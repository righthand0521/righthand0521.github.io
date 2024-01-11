# expect(1) - programmed dialogue with interactive programs, Version 5

```bash
apt install expect -y
```

## ./expect.exp

<details><summary>vim expect.exp</summary>

```text
#!/usr/bin/expect -f

set IP [lindex $argv 0]
puts $IP
if { [string compare $IP ""] == 0 } {
    set IP "127.0.0.1"
} else {
    set IP "192.168.0.1"
}
puts $IP
```

```text
#!/usr/bin/expect -f

set TestData "True_0@False_1"
puts $TestData

set TestDataSplit [split $TestData "@"]
set TestDataSplitLength [llength $TestDataSplit]
puts $TestDataSplitLength

set TestData1 [lindex $TestDataSplit 0]
puts $TestData1

set List1 [split $TestData1 "_"]
set Item1 [lindex $List1 0]
puts $Item1
set Item2 [lindex $List1 1]
puts $Item2
```

</details>

## sh expect.sh

<details><summary>vim expect.sh</summary>

```text
#!/bin/sh

HOST="192.168.0.1"
USER="admin"
PASS="password"

Step='
spawn ssh '$USER'@'$HOST'

expect "password:"
send "'$PASS'\r"
expect "$"

send "?\r"
expect "$"

send "enable\r"
expect "$"

send "show system\r"
expect "$"

send "exit\r"
expect "$"

send "logout\r"

expect eof
'

Result="$(expect -c "${Step}")"
echo "$Result"

exit 0
```

</details>

## autoexpect(1) - generate an Expect script from watching a session

```bash
autoexpect -f ssh.exp ssh root@192.168.0.1
```
