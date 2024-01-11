# Shell Script

- [explainshell.com](https://explainshell.com/)
- [Shell Style Guide](https://google.github.io/styleguide/shell.xml)
- [Bash scripting cheatsheet](https://devhints.io/bash)
- [Shell & Utilities: Detailed Toc](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html)
- [pure-bash-bible](https://github.com/dylanaraps/pure-bash-bible)

## [shellcheck](https://github.com/koalaman/shellcheck)

```bash
apt install shellcheck -y
```

## Example

```bash
#!/bin/sh

ip2int() {
    local pIP="${1}"

    IFS=. read -r i1 i2 i3 i4 <<< "${pIP}"
    echo "$(((((((i1 << 8) | i2) << 8) | i3) << 8) | i4))"
}
int2ip() {
    local pINT="${1}"

    local pIP=""
    for i in 1 2 3 4; do
        pIP="$((pINT & 0xff))${pIP:+.}${pIP}"
        pINT="$((${pINT} >> 8))"
    done
    echo "${pIP}"
}
netmask() {
    local pINT="${1}"

    local mask="$((0xffffffff << (32 - ${pINT})))"
    int2ip "${mask}"
}
broadcast() {
    local addr="$(ip2int ${1})"
    local mask="$((0xffffffff << (32 -${2})))"

    int2ip "$((addr | ~mask))"
}
network() {
    local addr="$(ip2int ${1})"
    local mask="$((0xffffffff << (32 -${2})))"

    int2ip "$((addr & mask))"
}
mask2cdr () {
    local x=${1##*255.}
    set -- 0^^^128^192^224^240^248^252^254^ $(( (${#1} - ${#x})*2 )) ${x%%.*}
    x=${1%%$3*}
    echo $(( $2 + (${#x}/4) ))
}
cdr2mask () {
    set -- $(( 5 - ($1 / 8) )) 255 255 255 255 $(( (255 << (8 - ($1 % 8))) & 255 )) 0 0 0
    [ $1 -gt 1 ] && shift $1 || shift
    echo ${1-0}.${2-0}.${3-0}.${4-0}
}

ip2int "0.0.1.1"
int2ip "257"
netmask "24"
broadcast "192.168.1.1" "24"
network "10.1.1.1" "16"
mask2cdr "255.255.255.0"
cdr2mask "16"

exit 0
```

```bash
#!/bin/sh

decToBinary() {
    local pDec="${1}"
    printf "%s: " "${pDec}"

    local bits
    while true; do
        [ ${pDec} -le 0 ] && break

        bits="$((pDec&1))${bits}"
        pDec="$((pDec>>1))"
    done
    printf "%s\n" "${bits-0}"
}

decToBinary "$((RANDOM % 256))"

exit 0
```

```bash
#!/bin/sh

readFileLinbyLine() {
    local filename="${1}"

    while IFS='' read -r line || [ -n "${line}" ]; do
        echo "${LINENO}: ${line}"
    done < ${filename}
}

[ ${#} -lt 1 ] && echo "Usage: sh ${0} <File Path>" && exit 255
readFileLinbyLine "${1}"

exit 0
```

```bash
#/bin/sh

ftp_dir() {
    if [ $# -lt 4 ]; then
        echo "${LINENO}: Usage: ${FUNCNAME} <Host> <User> <Password> <Path>"
        return
    fi

    ftp -n ${1} <<END_SCRIPT
        quote USER ${2}
        quote PASS ${3}
        pass

        cd ${4}
        dir

        quit
END_SCRIPT
}

ftp_downloadFile() {
    if [ $# -lt 5 ]; then
        echo "${LINENO}: Usage: ${FUNCNAME} <Host> <User> <Password> <Path> <Download File>"
        return
    fi

    ftp -n ${1} <<END_SCRIPT
        quote USER ${2}
        quote PASS ${3}
        pass

        cd ${4}
        binary
        get ${5}

        quit
END_SCRIPT
}

ftp_uploadFile() {
    if [ $# -lt 5 ]; then
        echo "${LINENO}: Usage: ${FUNCNAME} <Host> <User> <Password> <Path> <Upload File>"
        return
    fi

    ftp -n ${1} <<END_SCRIPT
        quote USER ${2}
        quote PASS ${3}
        pass

        cd ${4}
        binary
        put ${5}

        quit
END_SCRIPT
}

ftp_deleteFile() {
    if [ $# -lt 5 ]; then
        echo "${LINENO}: Usage: ${FUNCNAME} <Host> <User> <Password> <Path> <Delete File>"
        return
    fi

    ftp -n ${1} <<END_SCRIPT
        quote USER ${2}
        quote PASS ${3}
        pass

        cd ${4}
        binary
        delete ${5}

        quit
END_SCRIPT
}

ftp_dir "192.168.0.1" "root" "password" "/root"
ftp_downloadFile "192.168.0.1" "root" "password" "/root" "download.tgz"
ftp_uploadFile "192.168.0.1" "root" "password" "/root" "upload.tgz"
ftp_deleteFile "192.168.0.1" "root" "password" "/root" "delete.tgz"

exit 0
```

```bash
#!/bin/sh

for ip in '8.8.8.8' '10.0.0.1'; do
    ping ${ip} -c 1 -W 1 &>/dev/null && ret=0 || ret=1
    echo "ping ${ip} -c 1 -W 1: ${ret}"
done

exit 0
```

```bash
#!/bin/sh

exString="../root/AbC/dE/111.sh"
printf "%24s\t%3d\n" "${exString}" "${#exString}"

printf "%24s\n" "$(echo ${exString} | tr '[:lower:]' '[:upper:]')"
printf "%24s\n" "$(echo ${exString} | awk '{print toupper($0)}')"

printf "%24s\n" "$(echo ${exString,,})"
printf "%24s\n" "$(echo ${exString} | tr '[:upper:]' '[:lower:]')"
printf "%24s\n" "$(echo ${exString} | awk '{print tolower($0)}')"

printf "%24s\n" "${exString:0:$((${#exString}-5))}"
printf "%24s\n" "${exString:1}"
printf "%24s\n" "${exString: -1}"

printf "%24s\n" "${exString%%/*}"
printf "%24s\n" "${exString#*/}"
printf "%24s\n" "${exString##*/}"

exit 0
```

```bash
#!/bin/sh

exArray=(
    "1:awk"
    "2:bzip2"
    "3:crontab"
)
for p in "${exArray[@]}"; do
    pKey="${p%%:*}"
    pValue="${p#*:}"

    printf "%s - %s\n" "${pKey}" "${pValue}"
done

childArray=(
    "ifconfig(8) - configure a network interface"
    "ip(8) - show / manipulate routing, network devices, interfaces and tunnels"
    "route(8) - show / manipulate the IP routing table"
)
parentArray=(
    "find(1) - search for files in a directory hierarchy"
    "grep(1) - print lines matching a pattern"
    "${childArray[@]}"
)

showArray() {
    for ((i=1; i<=${#}; i++)); do
        echo; echo "${LINENO}: ${!i}"

        echo "${LINENO}: ${!i%%-*}"
        echo "${LINENO}: ${!i#*-}"
    done
}
showArray "${parentArray[@]}"

exit 0
```

### Comment

```bash
<< Comment
    create multiline comments in Bash?
Comment
```

### trap

```bash
<< trap

trap: trap [-lp] [[arg] signal_spec ...]
    Trap signals and other events.

    Defines and activates handlers to be run when the shell receives signals
    or other conditions.

# trap -l
 1) SIGHUP   2) SIGINT   3) SIGQUIT  4) SIGILL   5) SIGTRAP
 6) SIGABRT  7) SIGBUS   8) SIGFPE   9) SIGKILL 10) SIGUSR1
11) SIGSEGV 12) SIGUSR2 13) SIGPIPE 14) SIGALRM 15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD 18) SIGCONT 19) SIGSTOP 20) SIGTSTP
21) SIGTTIN 22) SIGTTOU 23) SIGURG  24) SIGXCPU 25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF 28) SIGWINCH    29) SIGIO   30) SIGPWR
31) SIGSYS  34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX

trap
```

### [Colors and formatting](https://misc.flogisoft.com/bash/tip_colors_and_formatting)

```bash
readonly Black='\e[0;30m'
readonly Red='\e[0;31m'
readonly Green='\e[0;32m'
readonly Yellow='\e[0;33m'
readonly Blue='\e[0;34m'
readonly Magenta='\e[0;35m'
readonly Cyan='\e[0;36m'
readonly LightGray='\e[0;37m'
readonly NC='\e[0m'
```

### [Given the IP and netmask, how can I calculate the network address using bash?](https://stackoverflow.com/questions/15429420/given-the-ip-and-netmask-how-can-i-calculate-the-network-address-using-bash)

```bash
#!/bin/sh

IFS=. read -r i1 i2 i3 i4 <<< "192.168.1.1"
IFS=. read -r m1 m2 m3 m4 <<< "255.255.255.0"
printf "%d.%d.%d.%d\n" "$((i1 & m1))" "$((i2 & m2))" "$((i3 & m3))" "$((i4 & m4))"

IP=10.255.255.255
PREFIX=16
IFS=. read -r i1 i2 i3 i4 <<< $IP
IFS=. read -r xx m1 m2 m3 m4 <<< \
    $(for a in $(seq 1 32); do \
        if [ $(((a - 1) % 8)) -eq 0 ]; then echo -n .; fi; \
        if [ $a -le $PREFIX ]; then echo -n 1; else echo -n 0; fi; \
    done)
printf "%d.%d.%d.%d\n" "$((i1 & (2#$m1)))" "$((i2 & (2#$m2)))" "$((i3 & (2#$m3)))" "$((i4 & (2#$m4)))"

exit 0
```

### [timestamp - periodically write time stamp](http://www.shelldorado.com/scripts/cmds/timestamp.txt)

```bash
#/bin/sh

Interval=${1:-1}
case "${Interval}" in
    *[0-9]*)
        ;;
    *)
        echo >&2 "usage: ${0} [Interval]
    Prints current time all <Interval> seconds"
        exit 1
        ;;
esac

while true; do
    echo "--$(date "+%Y-%m-%d %T")--"
    sleep ${Interval}
done

exit 0
```
