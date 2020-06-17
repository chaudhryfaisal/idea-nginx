static ngx_command_t  auth_jwt_commands[] = {

    { ngx_string("auth_jwt"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LMT_CONF|NGX_CONF_1MORE,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("auth_jwt_claim_set"),
      NGX_HTTP_MAIN_CONF|NGX_CONF_2MORE,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("auth_jwt_header_set"),
      NGX_HTTP_MAIN_CONF|NGX_CONF_2MORE,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("auth_jwt_key_file"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LMT_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("auth_jwt_key_request"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LMT_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("auth_jwt_leeway"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

   ngx_null_command

};

static ngx_http_variable_t ngx_http_echo_variables[] = {

    { ngx_string("jwt_header_"), NULL, ngx_http_variable_cookie,
      0, NGX_HTTP_VAR_PREFIX, 0 },
    { ngx_string("jwt_claim_"), NULL, ngx_http_variable_cookie,
      0, NGX_HTTP_VAR_PREFIX, 0 },

    { ngx_null_string, NULL, NULL, 0, 0, 0 }
};
