PHP_ARG_WITH(phpwkhtmltox, [for libwkhtmltox support],
[  --with-phpwkhtmltox=[DIR]     Include libwkhtmltox support])

if test "$PHP_PHPWKHTMLTOX" != "no"; then
    for i in $PHP_PHPWKHTMLTOX /usr /usr/local /opt; do
        if test -f $i/include/wkhtmltox/pdf.h; then
            WKHTMLTOX_LIB_DIR=$i/lib
            WKHTMLTOX_INC_DIR=$i/include
            AC_MSG_RESULT([found in $i]) 
        fi
    done
    
    if test -z "$WKHTMLTOX_LIB_DIR" -o -z "$WKHTMLTOX_INC_DIR"; then
        AC_MSG_RESULT([not found])
        AC_MSG_ERROR([Please install libwkhtmltox])
    fi
    
    PHP_CHECK_LIBRARY(wkhtmltox, wkhtmltopdf_init, 
        [
        PHP_ADD_LIBRARY_WITH_PATH(wkhtmltox, $WKHTMLTOX_LIB_DIR, PHPWKHTMLTOX_SHARED_LIBADD)
        AC_DEFINE(HAVE_PHPWKHTMLTOX, 1, [libwkhtmltox passed])
        ],
        [AC_MSG_ERROR([libwkhtmltox version 0.10 or later required])],
        [-L$WKHTMLTOX_LIB_DIR -R$WKHTMLTOX_LIB_DIR])
    
    PHP_SUBST(PHPWKHTMLTOX_SHARED_LIBADD)
    PHP_ADD_INCLUDE($WKHTMLTOX_INC_DIR)
    PHP_NEW_EXTENSION(phpwkhtmltox, phpwkhtmltox.c, $ext_shared)
fi