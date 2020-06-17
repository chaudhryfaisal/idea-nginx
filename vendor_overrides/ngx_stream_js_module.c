static ngx_command_t  auth_jwt_commands[] = {

    { ngx_string("js_access"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("js_filter"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("js_import"),
      NGX_STREAM_SRV_CONF|NGX_CONF_TAKE4,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("js_include"),
      NGX_STREAM_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("js_path"),
      NGX_HTTP_MAIN_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("js_preread"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("js_set"),
      NGX_STREAM_SRV_CONF|NGX_CONF_TAKE3,
      ngx_void_callback,
      0,
      0,
      NULL },

   ngx_null_command

};

