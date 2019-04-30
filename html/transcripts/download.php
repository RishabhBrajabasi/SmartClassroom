<?php
  if ($handle = opendir('.')) {
    while (false !== ($file = readdir($handle))) {
      if ($file != "." && $file != ".." && $file != "download.php") {
        $thelist .= '<li><a href="'.$file.'" download>'.$file.'</a></li>';
      }
    }
    closedir($handle);
  }
?>
<h1>Transcripts:</h1>
<ul><?php echo $thelist; ?></ul>