PHP_ARG_WITH(phpwkhtmltox, [for libwkhtmltox support],
[--with-phpwkhtmltox Include libwkhtmltox support])

if test "$PHP_PHPWKHTMLTOX" != "no"; then
    for i in /usr /usr/local /opt; do
        if test -f $i/include/wkhtmltox/pdf.h; then
            WKHTMLTOX_DIR=$i
        fi
    done
    
    PHP_CHECK_LIBRARY(wkhtmltox, wkhtmltopdf_init, 
        [
        PHP_ADD_LIBRARY_WITH_PATH(wkhtmltox, $WKHTMLTOX_DIR/lib, PHPWKHTMLTOX_SHARED_LIBADD)
        PHP_ADD_INCLUDE($WKHTMLTOX_DIR/include)
        AC_DEFINE(HAVE_PHPWKHTMLTOX, 1, [libwkhtmltox passed])
        ],
        [AC_MSG_ERROR([libwkhtmltox version 0.10 or later required])],
        [-L$WKHTMLTOX_DIR/lib])
    
    PHP_SUBST(PHPWKHTMLTOX_SHARED_LIBADD)
    PHP_NEW_EXTENSION(phpwkhtmltox, phpwkhtmltox.c, $ext_shared)
fi