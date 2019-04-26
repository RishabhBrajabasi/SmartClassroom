<?php
$myfile = fopen("file.txt", "w") or die("Unable to open file!");
$txt = "1";
fwrite($myfile, $txt);
fclose($myfile);
$myfile = fopen("file.txt", "w") or die("Unable to open file!");
$txt = "0";
fwrite($myfile, $txt);
fclose($myfile);
// header('location: index_3.html');
exit;
?>
