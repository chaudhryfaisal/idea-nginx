static ngx_command_t  auth_jwt_commands[] = {

    { ngx_string("keyval"),
      NGX_HTTP_MAIN_CONF|NGX_CONF_TAKE3,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("keyval_zone"),
      NGX_HTTP_MAIN_CONF|NGX_CONF_1MORE,
      ngx_void_callback,
      0,
      0,
      NULL },

   ngx_null_command

};

