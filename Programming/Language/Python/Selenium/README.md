# [Selenium](https://www.selenium.dev/)

- [GitHub](https://github.com/SeleniumHQ/)

```bash
pip install selenium
```

## [WebDriver](https://www.selenium.dev/documentation/webdriver/)

### Google Chrome

- [ChromeDriver](https://chromedriver.chromium.org)

```bash
chromedriver -v
```

- [google-chrome-stable](https://www.ubuntuupdates.org/package/google_chrome/stable/main/base/google-chrome-stable)

```bash
google-chrome --version
```

- vim /usr/bin/google-chrome

```bash
exec -a "$0" "$HERE/chrome" "$@" --no-sandbox
```

### Mozilla Firefox

- [geckodriver](https://github.com/mozilla/geckodriver)

### Internet Explorer

- [IE Driver Server](https://www.selenium.dev/documentation/ie_driver_server)

## [Selenium Grid](https://www.selenium.dev/documentation/grid/)

```bash
java -jar selenium-server-<version>.jar standalone

java -jar selenium-server-standalone-3.14.0.jar
```
