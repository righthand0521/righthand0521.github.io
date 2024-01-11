<?php
	$css = '
<style type="text/css">
	a {
		text-decoration: none;
		color: #0066CC;
	}
	a:link {
		text-decoration: none;
		color: #0066CC;
	}
	a:visited {
		text-decoration: none;
		color: #0066CC;
	}
	a:hover {
		text-decoration: none;
		color: #0066CC;
	}
</style>';
	print $css;

	echo "Today is " . date("Y-m-d") . "<br>";

	print '<table width="100%" style="border-collapse:collapse;" border="0"';
	print '<tr>';

	$path = '/home/svn/';
	if ($handle = opendir($path))
	{
		while (false !== ($project = readdir($handle)))
		{
			if (($project == '.') || ($project == '..') || ($project[0] == '.'))
				continue;

			if ($project == 'PROJ_XXX')
				continue;

			if (!is_dir($path . '/' . $project))
				continue;

			print '<td valign="top">';

			print '<h3>'. $project . '</h3>';
			if ($handle2 = opendir($path . '/' . $project))
			{
				$logs = array();
				while (false !== ($logs[] = readdir($handle2)))	;

				sort($logs);
				closedir($handle2);

				foreach ($logs as $log)
				{
					if (strpos($log, '.log') !== false)
					{
						$url = '/Subversion/open.php?project=' . $project . '&log=' . $log;
						print '<a href="' . $url . '" target="_blank">' . $log . '</a>' . '<br>';
					}
				}
			}

			print '</td>';
		}
		closedir($handle);
	}

	print '</tr>';
	print '</table>';
?>
