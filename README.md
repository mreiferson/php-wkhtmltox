PHP bindings for the fabulous `libwkhtmltox`

Special thanks to antialize for creating [wkhtmltopdf](http://wkhtmltopdf.org)

For parameters and settings (for users familiar with the command line utility) see:

    http://wkhtmltopdf.org/libwkhtmltox/pagesettings.html

### Installation

    $ phpize
    $ ./configure
    $ make install

edit your `php.ini` and add:

    extension=phpwkhtmltox.so

### Tested on:

 * CentOS 5.5, PHP 5.3.3 (64-bit)
 * Mac OSX 10.6.4 Snow Leopard, PHP 5.2.12 (64-bit)

### Pre-requisites on all platforms:

 * you need `libwkhtmltox.*` somewhere in your LD path (`/usr/local/lib`)
 * you need the directory `src/include/wkhtmltox` from `wkhtmltopdf` somewhere on your include path (`/usr/local/include`)

### OSX Notes:
Until [this bug](http://bugreports.qt-project.org/browse/QTBUG-5952) is fixed you need `qt_menu.nib` directory from the QT source tree in the same directory as your `libwkhtmltox.*` library files
