#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "phpwkhtmltox.h"
#include "wkhtmltox/pdf.h"
#include "wkhtmltox/image.h"

static function_entry phpwkhtmltox_functions[] = {
    PHP_FE(wkhtmltox_pdf_init, NULL)
    PHP_FE(wkhtmltox_image_init, NULL)
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
    php_info_print_table_row(2, "phpwkhtmltox Module", "enabled");
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

PHP_FUNCTION(wkhtmltox_pdf_init)
{
    wkhtmltopdf_init(0);
}

PHP_FUNCTION(wkhtmltox_image_init)
{
    wkhtmltoimage_init(0);
}