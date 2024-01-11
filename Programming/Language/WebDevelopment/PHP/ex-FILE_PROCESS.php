<?php
	class FILE_PROCESS {
		function open_file($fileName) {
			if (!isset($this))
			{
				print __CLASS__ . " is not defined." . PHP_EOL;
				return;
			}

			if (!file_exists($fileName))
			{
				print $fileName . " does not exist" . PHP_EOL;
				return;
			}

			print $fileName . " exists" . PHP_EOL;
			$file = fopen($fileName, "r");
			while (!feof($file))
			{
				$value = fgets($file);
				if (empty($value))
				{
					continue;
				}
				print "&nbsp&nbsp&nbsp&nbsp" . $value;
			}
			fclose($file);
		}
		function scan_dir($dirName) {
			if (!isset($this))
			{
				print __CLASS__ . " is not defined." . PHP_EOL;
				return;
			}

			if (!file_exists($dirName))
			{
				print $dirName . " does not exist" . PHP_EOL;
				return;
			}

			print $dirName . " exists" . PHP_EOL;
			if (false == ($handle = opendir($dirName)))
			{
				print $dirName . " handle fail" . PHP_EOL;
				return;
			}

			while (false != ($entry = readdir($handle)))
			{
				if (($entry==".") || ($entry==".."))
				{
					continue;
				}

				print "&nbsp&nbsp&nbsp&nbsp" . $entry.PHP_EOL;
			}
			closedir($handle);
		}
	}

	$classVar = new FILE_PROCESS;
	$classVar->open_file(__DIR__."/data.txt");
	$classVar->scan_dir(__DIR__);
?>
