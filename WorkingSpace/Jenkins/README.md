# [Jenkins](https://www.jenkins.io/zh/)

- [jenkinsci/jenkins](https://github.com/jenkinsci/jenkins)
- [jenkinsci/email-ext-plugin](https://github.com/jenkinsci/email-ext-plugin)

## [Install](https://www.jenkins.io/doc/book/installing/linux/)

- [Docker Hub](https://hub.docker.com/_/jenkins)

```bash
apt-cache search openjdk | grep openjdk-17
apt install openjdk-17-jdk -y

javac -version
java -version
```

```bash
wget -O /usr/share/keyrings/jenkins-keyring.asc https://pkg.jenkins.io/debian-stable/jenkins.io-2023.key
echo "deb [signed-by=/usr/share/keyrings/jenkins-keyring.asc]" https://pkg.jenkins.io/debian-stable binary/ | \
tee /etc/apt/sources.list.d/jenkins.list

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

```bash
apt remove --purge jenkins
apt remove jenkins
apt remove --auto-remove jenkins
```

## Configure

```bash
cat /var/lib/jenkins/secrets/initialAdminPassword
```

- vim /var/lib/jenkins/config.xml

```bash
<useSecurity>false</useSecurity>
```

- vim /etc/default/jenkins

```bash
JENKINS_USER=root
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
apt-get update
apt-get --only-upgrade install jenkins
systemctl restart jenkins
```

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

### [Robot Framework](https://plugins.jenkins.io/robot/)

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

### [Parameterized Trigger](https://plugins.jenkins.io/parameterized-trigger/)

- [Jenkins Job 觸發其他需要參數的 Job](https://blog.yowko.com/jenkins-job-trigger-paramerized-job/)

### [Parameterized Scheduler](https://plugins.jenkins.io/parameterized-scheduler/)

### [Environment Injector](https://plugins.jenkins.io/envinject/)

### [Log Parser](https://plugins.jenkins.io/log-parser/)

- vim /root/Jenkins/LogParser

```bash
error /^ERROR/
```

### [Config File Provider](https://plugins.jenkins.io/config-file-provider/)

### [Zentimestamp](https://plugins.jenkins.io/zentimestamp/)

### [Email Extension Template](https://plugins.jenkins.io/emailext-template/)

### [Blue Ocean](https://plugins.jenkins.io/blueocean/)

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
