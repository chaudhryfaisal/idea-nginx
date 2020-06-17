static ngx_command_t  auth_jwt_commands[] = {

    { ngx_string("api"),
      NGX_HTTP_LOC_CONF|NGX_CONF_ANY,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("status_zone"),
      NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

   ngx_null_command

};

