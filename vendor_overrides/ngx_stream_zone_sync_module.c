static ngx_command_t  auth_jwt_commands[] = {

    { ngx_string("zone_sync"),
      NGX_HTTP_SRV_CONF|NGX_CONF_NOARGS,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_buffers"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE2,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_connect_retry_interval"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_connect_timeout"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_interval"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_recv_buffer_size"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_server"),
      NGX_HTTP_SRV_CONF|NGX_CONF_1MORE,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl_certificate"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl_certificate_key"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl_ciphers"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl_crl"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl_name"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl_password_file"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl_protocols"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_ANY,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl_server_name"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl_trusted_certificate"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl_verify"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_ssl_verify_depth"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

    { ngx_string("zone_sync_timeout"),
      NGX_STREAM_SRV_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_TAKE1,
      ngx_void_callback,
      0,
      0,
      NULL },

   ngx_null_command

};
