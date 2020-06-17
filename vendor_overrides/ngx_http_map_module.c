static ngx_command_t  auth_jwt_commands[] = {

    { ngx_string("map"),
      NGX_HTTP_MAIN_CONF|NGX_CONF_2MORE,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("map_hash_bucket_size"),
      NGX_HTTP_MAIN_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("map_hash_max_size"),
      NGX_HTTP_MAIN_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

   ngx_null_command

};

