<?php
  if ($handle = opendir('files')) {
    while (false !== ($file = readdir($handle))) {
      if ($file != "." && $file != "..") {
        $thelist .= '<li><a href="'.$file.'" download>'.$file.'</a></li>';
      }
    }
    closedir($handle);
  }
?>
<h1>Transcripts:</h1>
<ul><?php echo $thelist; ?></ul>