#ifndef PHP_PHPWKHTMLTOX_H
#define PHP_PHPWKHTMLTOX_H true

#define PHP_PHPWKHTMLTOX_VERSION "0.10"
#define PHP_PHPWKHTMLTOX_EXTNAME "phpwkhtmltox"

PHP_FUNCTION(wkhtmltox_pdf_init);
PHP_FUNCTION(wkhtmltox_image_init);

extern zend_module_entry phpwkhtmltox_module_entry;
#define phpext_phpwkhtmltox_ptr &phpwkhtmltox_module_entry

#endif