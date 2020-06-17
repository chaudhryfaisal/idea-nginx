#!/usr/bin/env sh

clone (){
    path=$3$2
    git clone --depth 1 $1 $path
}
module (){
    clone https://github.com/$1/$2.git $2 nginx/src/modules/
}

rm -rf vendor; mkdir -p vendor; cd vendor
clone "https://github.com/nginx/nginx.git" nginx
clone "https://github.com/openresty/lua-nginx-module.git" lua-nginx-module

module openresty set-misc-nginx-module
module openresty headers-more-nginx-module
module openresty replace-filter-nginx-module
module openresty echo-nginx-module
module openresty redis2-nginx-module
module yaoweibin ngx_http_substitutions_filter_module
module nginx njs

cp -r ../vendor_overrides nginx/src/overrides