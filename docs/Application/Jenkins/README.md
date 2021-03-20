[Jenkins](https://www.jenkins.io/zh/)
===
### Install
```
make sure Java 8 is the default Java version because Jenkins does not support newer version
# apt install openjdk-8-jdk -y
# javac -version
javac 1.8.0_191
# java -version
openjdk version "1.8.0_191"
OpenJDK Runtime Environment (build 1.8.0_191-8u191-b12-0ubuntu0.16.04.1-b12)
OpenJDK 64-Bit Server VM (build 25.191-b12, mixed mode)

# wget -q -O - http://pkg.jenkins-ci.org/debian/jenkins-ci.org.key | sudo apt-key add -
# sh -c 'echo deb http://pkg.jenkins-ci.org/debian binary/ > /etc/apt/sources.list.d/jenkins.list'
# apt update
# apt install jenkins -y
# systemctl status jenkins
# cat /var/lib/jenkins/secrets/initialAdminPassword
# vim /var/lib/jenkins/config.xml
<useSecurity>false</useSecurity>
# vim /etc/sudoers
jenkins ALL=(ALL:ALL) NOPASSWD:ALL
```
### Update
```
# cd /usr/share/jenkins
# service jenkins stop
# grep -in "<version>" /var/lib/jenkins/config.xml
# wget https://updates.jenkins-ci.org/latest/jenkins.war
# service jenkins start
```
---
### Build: Execute shell
```
export DISPLAY=:0
```
### Plugin: Robot Framework
```
${SCRIPT,template="email-template.groovy"}
```
---
### [Docker Hub](https://hub.docker.com/_/jenkins)
```
# docker pull jenkins
# docker pull jenkins/jenkins:lts

This will store the workspace in /var/jenkins_home.
All Jenkins data lives in there - including plugins and configuration.
# docker run -p 8080:8080 -p 50000:50000 jenkins
# docker exec jenkins cat /var/jenkins_home/secrets/initialAdminPassword

This will store the jenkins data in /your/home on the host.
Ensure that /your/home is accessible by the jenkins user in container (jenkins user - uid 1000) or use -u some_other_user parameter with docker run.
# docker run --name myjenkins -p 8080:8080 -p 50000:50000 -v /var/jenkins_home jenkins
# docker run -d --name myjenkins -p 8080:8080 -p 50000:50000 -v /var/jenkins_home jenkins
# docker exec myjenkins cat /var/jenkins_home/secrets/initialAdminPassword

Update
# docker container exec -u 0 -it myjenkins bash
# wget https://updates.jenkins-ci.org/latest/jenkins.war
# mv jenkins.war /usr/share/jenkins
# chown jenkins:jenkins /usr/share/jenkins/jenkins.war
# exit
# docker container restart myjenkins
```
---
