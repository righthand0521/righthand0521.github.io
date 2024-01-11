# [PHP](https://www.php.net/)

## [phpinfo](https://www.php.net/manual/en/function.phpinfo.php)

```php
<?php
    phpinfo();
?>
```

## [PHP_EOL](https://www.runoob.com/w3cnote/php-php_eol.html)

```php
<?php
    echo PHP_EOL;
    print PHP_EOL;
?>
```

## [error_reporting](https://www.php.net/manual/en/function.error-reporting)

```php
<?php
    // Turn off error reporting
    error_reporting(0);

    // Report runtime errors
    error_reporting(E_ERROR | E_WARNING | E_PARSE);

    // Report all errors
    error_reporting(E_ALL);

    // Report all errors except E_NOTICE
    error_reporting(E_ALL & ~E_NOTICE);
?>
```

## MAGIC_CONSTANTS

```php
<?php
    namespace ExampleProject;
    class MAGIC_CONSTANTS {
        function display() {
            // The current line number of the file.
            print "__LINE__: " . __LINE__ . PHP_EOL;

            // The full path and filename of the file with symlinks resolved.
            // If used inside an include, the name of the included file is returned.
            print "__FILE__: " . __FILE__ . PHP_EOL;

            // The directory of the file.
            // If used inside an include, the directory of the included file is returned.
            // This is equivalent to dirname(__FILE__).
            // This directory name does not have a trailing slash unless it is the root directory.
            print "__DIR__: " . __DIR__ . PHP_EOL;

            // The function name.
            print "__FUNCTION__: " . __FUNCTION__ . PHP_EOL;

            // The class name.
            // The class name includes the namespace it was declared in (e.g. Foo\Bar).
            // Note that as of PHP 5.4 __CLASS__ works also in traits.
            // When used in a trait method, __CLASS__ is the name of the class the trait is used in.
            print "__CLASS__: " . __CLASS__ . PHP_EOL;

            // The trait name.
            // The trait name includes the namespace it was declared in (e.g. Foo\Bar).
            print "__TRAIT__: " . __TRAIT__ . PHP_EOL;

            // The class method name.
            print "__METHOD__: " . __METHOD__ . PHP_EOL;

            // The name of the current namespace.
            print "__NAMESPACE__: " . __NAMESPACE__ . PHP_EOL;

            // The fully qualified class name.
            print "MAGIC_CONSTANTS::class: " . MAGIC_CONSTANTS::class . PHP_EOL;
        }
    }

    print "<pre>" . PHP_EOL;
    $classVar = new MAGIC_CONSTANTS;
    $classVar->display();
    print "</pre>" . PHP_EOL;
?>
```

## [header](https://www.php.net/manual/en/function.header.php)

```php
<?php
    header("Location: http://" . $_SERVER["HTTP_HOST"] . "/index.html" );
    exit();
?>
```
