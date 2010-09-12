#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "phpwkhtmltox.h"
#include "wkhtmltox/pdf.h"
#include "wkhtmltox/image.h"

static function_entry phpwkhtmltox_functions[] = {
    PHP_FE(wkhtmltox_convert, NULL)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(phpwkhtmltox)
{
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(phpwkhtmltox)
{
    return SUCCESS;
}

PHP_RINIT_FUNCTION(phpwkhtmltox)
{
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(phpwkhtmltox)
{
    return SUCCESS;
}

PHP_MINFO_FUNCTION(phpwkhtmltox)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "phpwkhtmltox", "enabled");
    php_info_print_table_row(2, "version", wkhtmltopdf_version());
    php_info_print_table_end();
}

zend_module_entry phpwkhtmltox_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_PHPWKHTMLTOX_EXTNAME,
    phpwkhtmltox_functions,
    PHP_MINIT(phpwkhtmltox),
    PHP_MSHUTDOWN(phpwkhtmltox),
    PHP_RINIT(phpwkhtmltox),
    PHP_RSHUTDOWN(phpwkhtmltox),
    PHP_MINFO(phpwkhtmltox),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_PHPWKHTMLTOX_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PHPWKHTMLTOX
ZEND_GET_MODULE(phpwkhtmltox)
#endif

PHP_FUNCTION(wkhtmltox_convert)
{
    char *input;
    int input_len;
    
    char *output;
    int output_len;
    
    zval *params;
    zval **data;
    HashTable *params_hash;
    HashPosition pointer;
    int params_count;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssa", 
            &input, &input_len, &output, &output_len, &params) == FAILURE) {
        RETURN_NULL();
    }
    
    params_hash = Z_ARRVAL_P(params);
    params_count = zend_hash_num_elements(params_hash);
    for(zend_hash_internal_pointer_reset_ex(params_hash, &pointer); 
            zend_hash_get_current_data_ex(params_hash, (void **)&data, &pointer) == SUCCESS; 
            zend_hash_move_forward_ex(params_hash, &pointer)) {
        zval temp = **data;
        zval_copy_ctor(&temp);
        convert_to_string(&temp);
        
        zval_dtor(&temp);
    }
    
    wkhtmltopdf_init(false);
    wkhtmltopdf_global_settings *global_settings = wkhtmltopdf_create_global_settings();
    wkhtmltopdf_object_settings *object_settings = wkhtmltopdf_create_object_settings();
    wkhtmltopdf_set_global_setting(global_settings, "out", output);
    wkhtmltopdf_set_object_setting(object_settings, "page", input);
    wkhtmltopdf_converter *c = wkhtmltopdf_create_converter(global_settings);
    wkhtmltopdf_add_object(c, object_settings, NULL);
    wkhtmltopdf_convert(c);
    wkhtmltopdf_destroy_converter(c);
    wkhtmltopdf_deinit();
    
    RETURN_TRUE;
}