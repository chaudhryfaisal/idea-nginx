//    https://www.nginx.com/resources/wiki/extending/api/configuration/

import java.util.regex.Pattern

class NginxDocsToCode {
    static final Pattern P_DIRECTIVE = Pattern.compile('<table (.*?)<\\/table>', Pattern.MULTILINE | Pattern.DOTALL)
    static final String P_ARG_VARIABLE = '\\{? ?\\.{3} ?\\}?'
    static final String P_ARG_OPTIONAL = ' ?\\[.*?\\]'
    static final String BASE_DIR = System.getProperty('BASE_DIR', '.')
    static final String DIRECTIVE_OUTPUT_DIR = BASE_DIR + '/resources/docs/directives/'
    static final String C_CODE_OUTPUT_DIR = BASE_DIR + '/vendor_overrides/'
    static final boolean DEBUG = false


    static void main(String[] args) {
        println("CWD:${new File('.').absolutePath}\n\n")
//        generateHTMLDocsFromNginxDoc()
        generateCodeForNginxPlusModules()
    }


    static void generateCodeForNginxPlusModules() {
        String modules
        modules = 'http/ngx_http_api_module http/ngx_http_keyval_module http/ngx_http_auth_jwt_module http/ngx_http_js_module stream/ngx_stream_zone_sync_module stream/ngx_stream_js_module'
        modules = 'http/ngx_http_map_module'
        modules.split(' ').each { mod ->
            println(mod)
//            def module = generateFromURL("http://nginx.org/en/docs/${mod}.html")
            def module = generateFromFile("src/main/resources/${mod}.html")
            if (module) {
//                module.dump()
                writeAsCode(module)
            }
        }
    }

    static void generateHTMLDocsFromNginxDoc() {
        String base = 'http://nginx.org/en/docs/'
        def modules = base.toURL().text.findAll('href="([a-z_\\/]+_module.html)">') { m, url -> base + url }
        modules.each { String mod ->
            println(mod)
            def module = generateFromURL(mod)
            if (module) {
                writeHtmlDescription(module)
            }
        }
    }

    static Module generateFromURL(String url) {
        try {
            return build(url.toURL().text, url)
        } catch (ignore) {
        }
        null

    }

    static Module generateFromFile(String path) {
        def mod = null
        def file = new File(path)
        file.exists() ? mod = build(file.text, path) : System.err.println("Missing ${file.absolutePath}")
        mod

    }

    static Module build(String html, String source) {
        List<Directive> directives = []
        Set<String> variables = []
        String title = html.find('<title>Module (.*?)</title>') { m, t -> t }
        html.findAll('<dt id="var_(.*?)"') { m, String v -> variables.add(v) }
        html.split('<div class="directive">').eachWithIndex { String block, int i ->
            if (i > 0) {
                block.replaceAll("[\r\n]", '').find(P_DIRECTIVE) { _, m ->
                    m.replaceAll(' {2,}', ' ').
                            find('Syntax:.*?<strong>(.*?)<\\/strong>(.*?)<\\/td>.*?Context:(.*?)<\\/td>')
                                    { _d, String name, String args, String context -> directives.add(new Directive(name: name, html: block.replaceAll("[\r\n]+", '\n'), args: buildArgs(args), context: buildContext(context))) }

                }
            }
        }
        new Module(name: title, directives: directives, variables: variables, source: source)
    }

    static Set<String> buildArgs(String args) {
        Set set = []
        args = args?.replaceAll('<[^>]*>', '')?.replaceAll(';', '')?.replaceAll(' \\| ', '|')?.trim()

        if (!args || args.length() == 0)
            set.add('NGX_CONF_NOARGS')
        else if ('on|off' === args)
            set.add('NGX_CONF_FLAG')
        else {
            def optional = args.findAll(P_ARG_OPTIONAL)
            def variable = args.find(P_ARG_VARIABLE)
            if (optional || variable) {
                def a = args;
                if (optional) a = a.replaceAll(P_ARG_OPTIONAL, '')
                if (variable) a = a.replaceAll(P_ARG_VARIABLE, '')
                set.add(a ? 'NGX_CONF_' + a.split(' ').length + 'MORE' : 'NGX_CONF_ANY')

            } else
                set.add('NGX_CONF_TAKE' + args.split(' ').length)
        }
        if (DEBUG) println("\tbuildArgs -> $set <- '$args'")
        set
    }

    static Set<String> buildContext(String context) {
        Set set = []
        context = context?.replaceAll('<[^>]*>', '')?.trim()
        context.split(',').each { c ->
            switch (c.trim()) {
                case 'server': set.add('NGX_HTTP_SRV_CONF'); break
                case 'http': set.add('NGX_HTTP_MAIN_CONF'); break
                case 'location': set.add('NGX_HTTP_LOC_CONF'); break
                case 'upstream': set.add('NGX_HTTP_UPS_CONF'); break
                case 'if': set.add('NGX_HTTP_SIF_CONF'); break // TODO validate
                case 'if in location': set.add('NGX_HTTP_LIF_CONF'); break
                case 'limit_except': set.add('NGX_HTTP_LMT_CONF'); break
                case 'any': set.add('NGX_ANY_CONF'); break
                case 'main': set.add('NGX_MAIN_CONF'); break
                case 'mail': set.add('NGX_MAIL_MAIN_CONF'); break
                case 'stream': set.add('NGX_STREAM_SRV_CONF'); break
                case 'events': set.add('NGX_EVENT_CONF'); break
                default: System.err.println('Unknown Context ' + c); set.add('UNKNOWN_CONTEXT');
            }
        }
        if (DEBUG) println("\tbuildContext -> $set <- '$context'")
        set
    }

    static void writeAsCode(Module module) {
        StringBuilder sb = new StringBuilder()
        if (module.directives) {
            sb.append('static ngx_command_t  auth_jwt_commands[] = {\n\n')
            module.directives.each { d ->
                sb.append("    { ngx_string(\"${d.name}\"),\n" +
                        "      ${d.contextAndArgs().join('|')},\n" +
                        "      ngx_void_callback,\n" +
                        "      0,\n" +
                        "      0,\n" +
                        "      NULL },\n\n")
            }
            sb.append('   ngx_null_command\n\n};\n\n')
        }
        if (module.variables) {
            sb.append('static ngx_http_variable_t ngx_http_echo_variables[] = {\n\n')
            module.variables.each { v ->
                sb.append("    { ngx_string(\"${v}\"), NULL, ngx_http_variable_cookie,\n      0, NGX_HTTP_VAR_PREFIX, 0 },\n")
            }
            sb.append('\n    { ngx_null_string, NULL, NULL, 0, 0, 0 }\n};\n')
        }
        if (sb.length() > 0)
            new File(C_CODE_OUTPUT_DIR + module.name + '.c').write(sb.toString())
    }

    static void writeHtmlDescription(Module module) {
        module.directives.eachWithIndex { d, i ->
            String prefix = "<h2><span class=\"mw-headline\" id=\"${d.name}\"> ${d.name} </span></h2>"
            String postfix = module.source.startsWith('http') ? "\n<span>[<a href=\"${module.source}#${d.name}\">${d.name}</a>]</span>" : ''
            String content = String.format("%s\n%s\n%s\n", prefix, d.html, postfix)
            new File(DIRECTIVE_OUTPUT_DIR + d.name + '.html').write(content)
        }
    }

    static class Module {
        String name
        Set<String> variables
        Set<Directive> directives
        String source

        @Override
        String toString() {
            return "Module{" +
                    "variables=" + variables +
                    ", directives=" + directives +
                    '}';
        }

        void dump() {
            printf("%s\t%s\n\t%s\n", name, variables?.size() + ':' + directives?.size(), variables)
            directives.each { d ->
                printf("\t%s\n\t\t%s\n\t\t%s\n\t\t%s\n", d.name, d.args, d.context, d.html)
            }
        }
    }

    static class Directive {
        String name
        String html
        Set<String> args
        Set<String> context

        Set<String> contextAndArgs() {
            Set<String> set = []
            set.addAll(context)
            set.addAll(args)
            set
        }

        @Override
        String toString() {
            return "Directive{" +
                    "name='" + name + '\'' +
                    ", args=" + args +
                    ", context=" + context +
                    '}';
        }
    }

}
