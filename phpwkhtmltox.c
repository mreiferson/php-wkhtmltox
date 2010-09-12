#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>

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
    int ret;
    
    char *format;
    int format_len;
    
    zval *global_params;
    zval *object_params;
    
    // initialize optional object_params array
    ALLOC_INIT_ZVAL(object_params);
    array_init(object_params);
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa|a", 
            &format, &format_len, &global_params, &object_params) == FAILURE) {
        RETURN_NULL();
    }
    
    if (strcmp(format, "image") == 0) {
        wkhtmltoimage_init(false);
        
        wkhtmltoimage_global_settings *global_settings = wkhtmltoimage_create_global_settings();
        
        wkhtmltox_set_params((void *)global_settings, (fp)wkhtmltoimage_set_global_setting, global_params);
        
        wkhtmltoimage_converter *c = wkhtmltoimage_create_converter(global_settings, NULL);
        ret = wkhtmltoimage_convert(c);
        wkhtmltoimage_destroy_converter(c);
        
        wkhtmltoimage_deinit();
    } else if (strcmp(format, "pdf") == 0) {
        wkhtmltopdf_init(false);
        
        wkhtmltopdf_global_settings *global_settings = wkhtmltopdf_create_global_settings();
        wkhtmltopdf_object_settings *object_settings = wkhtmltopdf_create_object_settings();
        
        wkhtmltox_set_params((void *)global_settings, (fp)wkhtmltopdf_set_global_setting, global_params);
        wkhtmltox_set_params((void *)object_settings, (fp)wkhtmltopdf_set_object_setting, object_params);
        
        wkhtmltopdf_converter *c = wkhtmltopdf_create_converter(global_settings);
        wkhtmltopdf_add_object(c, object_settings, NULL);
        ret = wkhtmltopdf_convert(c);
        wkhtmltopdf_destroy_converter(c);
        
        wkhtmltopdf_deinit();
    }
    
    RETVAL_BOOL((bool)ret);
}

void wkhtmltox_set_params(void *settings, fp set_function, zval *params)
{
    zval **data;
    HashTable *params_hash;
    HashPosition pointer;
    int params_count;
    char *key;
    int key_len;
    long index;
    int ret;
    
    params_hash = Z_ARRVAL_P(params);
    params_count = zend_hash_num_elements(params_hash);
    for(zend_hash_internal_pointer_reset_ex(params_hash, &pointer); 
            zend_hash_get_current_data_ex(params_hash, (void **)&data, &pointer) == SUCCESS; 
            zend_hash_move_forward_ex(params_hash, &pointer)) {
        zval temp = **data;
        zval_copy_ctor(&temp);
        
        if (zend_hash_get_current_key_ex(params_hash, &key, &key_len, &index, 0, &pointer) == HASH_KEY_IS_STRING) {
            switch (Z_TYPE(temp)) {
                case IS_BOOL:
                    ret = set_function(settings, key, Z_BVAL(temp) ? "true" : "false");
                    break;
                default:
                    convert_to_string(&temp);
                case IS_STRING:
                    ret = set_function(settings, key, Z_STRVAL(temp));
                    break;
            }
        }
        
        zval_dtor(&temp);
    }
} 