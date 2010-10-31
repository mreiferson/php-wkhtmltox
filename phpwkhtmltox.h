#ifndef PHP_PHPWKHTMLTOX_H
#define PHP_PHPWKHTMLTOX_H

#define PHP_PHPWKHTMLTOX_VERSION "0.10"
#define PHP_PHPWKHTMLTOX_EXTNAME "phpwkhtmltox"

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(phpwkhtmltox)
int wkhtmltoimage_initialized;
int wkhtmltopdf_initialized;
ZEND_END_MODULE_GLOBALS(phpwkhtmltox)

#ifdef ZTS
#define PHPWKHTMLTOX_G(v) TSRMG(phpwkhtmltox_globals_id, zend_phpwkhtmltox_globals *, v)
#else
#define PHPWKHTMLTOX_G(v) (phpwkhtmltox_globals.v)
#endif

PHP_FUNCTION(wkhtmltox_convert);

typedef int (*fp)(void *settings, const char *name, const char *value);
void wkhtmltox_set_params(void *settings, fp set_function, zval *params);

extern zend_module_entry phpwkhtmltox_module_entry;
#define phpext_phpwkhtmltox_ptr &phpwkhtmltox_module_entry

#endif