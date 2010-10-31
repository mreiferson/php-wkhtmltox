<?php

foreach (range(1, 4) as $i) {
    wkhtmltox_convert('pdf', 
        array('out' => '/tmp/test'.$i.'.pdf', 'imageQuality' => '95'), // global settings
        array(
            array('page' => 'http://www.visionaryrenesis.com/'),
            array('page' => 'http://www.google.com/')
            )); // object settings
}

?>
