<?php
//	echo $_GET["project"] . "<br>";
//	echo $_GET["log"] . "<br>";
//	echo $_SERVER['SERVER_ADDR'];

	$fileName = "/home/svn/" . $_GET["project"] . "/" . $_GET["log"];
	$file = fopen($fileName, "r");
	while (!feof($file))
	{
		$value = fgets($file);
		print "&nbsp&nbsp" . $value . "<br>";
	}
	fclose($file);
?>
