<?php

wkhtmltox_convert('pdf', 
    array('out' => 'test.pdf', 'imageQuality' => '95'), // global settings
    array('page' => 'http://www.google.com/', 'web.printMediaType' => true)); // object settings

?>
