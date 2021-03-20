[JMeter](https://jmeter.apache.org/)
===
### Install
```
1. Download JMeter
https://jmeter.apache.org/download_jmeter.cgi

2. Installing OpenJDK 8(Java 8 is still the most widely-used version of Java)
# apt update; apt install openjdk-8-jdk -y
# java -version; javac -version
```
### Run the command from CLI console
```
# jmeter -n -t [jmx file] -l [results file] -e -o [Path to web report folder]
-n, --nongui, run JMeter in nongui mode
-t, --testfile <argument>, the jmeter test(.jmx) file to run. "-t LAST" will load last used file
-l, --logfile <argument>, the file to log samples to
-e, --reportatendofloadtests, generate report dashboard after load test
-o, --reportoutputfolder <argument>, output folder for report dashboard
```
### Note: an error occurred assistive technology not found org.gnome.accessibility.atkwrapper
```
# vim /etc/java-8-openjdk/accessibility.properties

#assistive_technologies=org.GNOME.Accessibility.AtkWrapper
```
---
