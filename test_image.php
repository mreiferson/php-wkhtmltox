<?php

wkhtmltox_convert('image', 
    array('out' => '/tmp/test.jpg', 'in' => 'http://www.google.com/')); // global settings

?>
