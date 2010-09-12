<?php

wkhtmltox_convert('pdf', array('out' => 'test.pdf', 'imageQuality' => '95'), array('page' => 'http://www.google.com/', 'printMediaType' => true));

?>
