# [Jenkins](https://www.jenkins.io/zh/)

- [jenkinsci/jenkins](https://github.com/jenkinsci/jenkins)
- [jenkinsci/email-ext-plugin](https://github.com/jenkinsci/email-ext-plugin)

## [Install](https://www.jenkins.io/doc/book/installing/linux/)

```bash
apt install openjdk-11-jdk -y
javac -version
java -version
```

```bash
wget -q -O - http://pkg.jenkins-ci.org/debian/jenkins-ci.org.key | sudo apt-key add -
sh -c 'echo deb http://pkg.jenkins-ci.org/debian binary/ > /etc/apt/sources.list.d/jenkins.list'

wget -q -O - https://pkg.jenkins.io/debian-stable/jenkins.io.key | apt-key add -
sh -c 'echo deb https://pkg.jenkins.io/debian-stable binary/ > /etc/apt/sources.list.d/jenkins.list'

apt update
apt install jenkins -y
systemctl status jenkins
```

```bash
All packages are up to date.
W: An error occurred during the signature verification. The repository is not updated and the previous index files will
be used. GPG error: http://pkg.jenkins-ci.org/debian binary/ Release: The following signatures couldn't be verified
because the public key is not available: NO_PUBKEY FCEF32E745F2C3D5
W: Failed to fetch http://pkg.jenkins-ci.org/debian/binary/Release.gpg  The following signatures couldn't be verified
because the public key is not available: NO_PUBKEY FCEF32E745F2C3D5
W: Some index files failed to download. They have been ignored, or old ones used instead.

apt-key adv --recv-keys --keyserver keyserver.ubuntu.com <NO_PUBKEY>
apt-key adv --recv-keys --keyserver keyserver.ubuntu.com FCEF32E745F2C3D5
```

### [Docker Hub](https://hub.docker.com/_/jenkins)

```bash
docker pull jenkins
docker pull jenkins/jenkins:lts
```

- This will store the workspace in /var/jenkins_home. All Jenkins data lives in there - including plugins and configuration.

```bash
docker run -p 8080:8080 -p 50000:50000 jenkins
docker exec jenkins cat /var/jenkins_home/secrets/initialAdminPassword
```

- This will store the jenkins data in /your/home on the host.
Ensure that /your/home is accessible by the jenkins user in container (jenkins user - uid 1000) or use -u some_other_user
parameter with docker run.

```bash
docker run --name myjenkins -p 8080:8080 -p 50000:50000 -v /var/jenkins_home jenkins
docker run -d --name myjenkins -p 8080:8080 -p 50000:50000 -v /var/jenkins_home jenkins
docker exec myjenkins cat /var/jenkins_home/secrets/initialAdminPassword
```

- Update

```bash
docker container exec -u 0 -it myjenkins bash
wget https://updates.jenkins-ci.org/latest/jenkins.war
mv jenkins.war /usr/share/jenkins
chown jenkins:jenkins /usr/share/jenkins/jenkins.war
exit
docker container restart myjenkins
```

## Configure

```bash
cat /var/lib/jenkins/secrets/initialAdminPassword
```

``` bash
# vim /var/lib/jenkins/config.xml
<useSecurity>false</useSecurity>
```

```bash
# vim /etc/sudoers
jenkins ALL=(ALL:ALL) NOPASSWD:ALL

# vim /etc/default/jenkins
JENKINS_USER=root

chown -R root:root /var/lib/jenkins
chown -R root:root /var/cache/jenkins
chown -R root:root /var/log/jenkins
```

```bash
service jenkins restart
ps -ef | grep jenkins

/usr/bin/java -Djava.awt.headless=true -jar /usr/share/java/jenkins.war --webroot=/var/cache/jenkins/war --httpPort=8080
/usr/bin/java -Djava.awt.headless=true \
-Dhudson.model.DirectoryBrowserSupport.CSP="sandbox allow-scripts; default-src 'none'; img-src 'self' data: ; \
style-src 'self' 'unsafe-inline' data: ; script-src 'self' 'unsafe-inline' 'unsafe-eval' ;" \
-jar /usr/share/java/jenkins.war --webroot=/var/cache/jenkins/war --httpPort=8080
```

## Update

```bash
cd /usr/share/jenkins
service jenkins stop
grep -in "<version>" /var/lib/jenkins/config.xml
wget https://updates.jenkins-ci.org/latest/jenkins.war
service jenkins start
```

## Jobs

### Remote Trig

```bash
curl -I -X POST "http://<ID>:<Token>@<IP Address>/job/<JOB_NAME>/buildWithParameters?<Parameters>=<Value>"
```

## Build: Execute shell

```bash
export DISPLAY=:0
```

## Plugin

### Robot Framework

```text
${SCRIPT,template="email-template.groovy"}
```

- [Error: Opening Robot Framework log failed](https://stackoverflow.com/questions/36607394/error-opening-robot-framework-log-failed#:~:text=To%20resolve%20your,your%20Jenkins%20build.)

```text
1. Connect on your Jenkins URL
2. Click on Manage Jenkins from left side panel.
3. Click on Script Console
4. Copy this into the field
System.setProperty("hudson.model.DirectoryBrowserSupport.CSP","sandbox allow-scripts; default-src 'none';
img-src 'self' data: ; style-src 'self' 'unsafe-inline' data: ; script-src 'self' 'unsafe-inline' 'unsafe-eval' ;")
5. Click on Run button.
6. Execute your Jenkins build.
```

- [robot-framework-email-template](https://github.com/mustafa-masetic/robot-framework-email-template)

### Parameterized Trigger Plugin

- [Jenkins Job 觸發其他需要參數的 Job](https://blog.yowko.com/jenkins-job-trigger-paramerized-job/)

### Parameterized Scheduler

### Environment Injector

### [Plugin - LogParser](https://plugins.jenkins.io/log-parser/)

```bash
# vim /root/Jenkins/LogParser
error /^ERROR/
```

### Config File Provider

## [Jenkinsfile](https://www.jenkins.io/doc/book/pipeline/jenkinsfile/)

### [pipeline](https://www.jenkins.io/doc/book/pipeline)

```Groovy
emailext body: '''${SCRIPT, template="managed:Groovy Email Template"}''',
```

## Question

<details><summary><a href="https://stackoverflow.com/questions/36547680/how-do-i-get-the-output-of-a-shell-command-executed-using-into-a-variable-from-j" target="_blank" style="color:gray">How do I get the output of a shell command executed using into a variable from Jenkinsfile (groovy)?</a></summary>

```groovy
script {
    GIT_COMMIT_EMAIL = sh (
        script: 'git --no-pager show -s --format=\'%ae\'',
        returnStdout: true
    ).trim()
    echo "Git committer email: ${GIT_COMMIT_EMAIL}"
}
```

</details>
