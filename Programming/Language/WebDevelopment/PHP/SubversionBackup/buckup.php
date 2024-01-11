<?php
	echo "Today is " . date("Y-m-d") . "<br>";

	print '<table width="100%" style="border-collapse:collapse;" border="0"';
	print '<tr>';

	$path = '/home/svn/';
	$ver = 'svnlook youngest /svn/mirrorLucidLynx/';
	if ($handle = opendir($path))
	{
		$rows = 0;
		while (false !== ($project = readdir($handle)))
		{
			if (($project == '.') || ($project == '..') || ($project[0] == '.'))
				continue;

			if ($project == 'PROJ_XXX')
				continue;

			if (!is_dir($path . '/' . $project))
				continue;

			$rows++;
			print '<td valign="top">';

			print '<h3>' . $project . ': ';
			system($ver . $project, $retval);
			print '</h3>';

			print '<pre>';
			system('ls ' . $path . $project .'/ | grep ".tar.gz"', $retval);
			print '</pre>';

			print '</td>';

			if ($rows%3 == 0)
				print '</tr><tr><td col="3" height="16px"></td></tr><tr>';
			
		}
		closedir($handle);
	}

	print '</tr>';
	print '</table>';
?>
