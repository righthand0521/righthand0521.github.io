# [Wireshark](https://www.wireshark.org/)

```bat
"C:\Program Files\Wireshark\Wireshark.exe" -h
"C:\Program Files\Wireshark\Wireshark.exe" -D
"C:\Program Files\Wireshark\Wireshark.exe" -i 2 -k -b filesize:51200 -w "<File Name>.pcap"
```

```bat
"C:\Program Files\Wireshark\mergecap.exe" -w <outfile> <infile1> <infile2>
```

```bat
"C:\Program Files\Wireshark\editcap.exe" -F pcap -c <packets per file> <infile> <outfile>
"C:\Program Files\Wireshark\editcap.exe" -F pcap -t <time adjustment> <infile> <outfile>
"C:\Program Files\Wireshark\editcap.exe" -F pcap -d <inDuplicateFile> <outDuplicateFile>
```

## editcap(1) - Edit and/or translate the format of capture files

```bash
find . -type f -name '*.pcap' -print0 | while IFS= read -r -d '' f; do editcap -F libpcap "$f" "${f%.pcapng}.pcap"; rm $f; done

editcap -F libpcap -T ether file.pcapng file.pcap
editcap -F libpcap file.pcapng file.pcap
editcap -F libpcap <ori file> <output file>
```

## pcapfix(1) - repair pcap and pcapng files

```bash
apt install pcapfix -y
```

```text
pcapfix-1.1.0-win32: pcapfix.exe
```

## Wireshark Dissector Plugin

- [S7comm Wireshark dissector plugin](https://sourceforge.net/projects/s7commwireshark/)
