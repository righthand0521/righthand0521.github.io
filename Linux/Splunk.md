# [Splunk](https://www.splunk.com/)

```bash
cd /opt; dpkg -i <splunk.deb>
cd /opt; rpm -ivh <splunk.rpm> --force
cd /opt; tar xzf splunk-<update new version>-Linux-x86_64.tgz
```

```bash
# vim /etc/bash.bashrc

export PATH=$PATH:/opt/splunk/bin
```

```bash
splunk help
splunk version

splunk status
splunk start
splunk restart
splunk stop
splunk enable boot-start
splunk disable boot-start

splunk clean eventdata
```

- 查看索引存儲的目錄

```bash
splunk show datastore-dir
```

- 可查看所有索引以及索引的目錄

```bash
splunk list index
```

```bash
# vim /opt/splunk/etc/system/default/props.conf

35:MAX_EVENTS = 256
```

## Search & Reporting - SPL(Search Processing Language)

```bash
host="ubuntu" | stats count by source
sourcetype=syslog | stats count by host
```
