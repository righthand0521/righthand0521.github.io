# VMware

## Workstation

```bat
"<vmplayer.exe install path>" "<.vmx Path>"
"C:\Program Files (x86)\VMware\VMware Workstation\vmplayer.exe" "D:\test.vmx"
```

### How to merge multiple vmdk’s into single vmdk

```bat
"C:\Program Files (x86)\VMware\VMware Workstation\vmware-vdiskmanager.exe" -r <original.vmdk> -t <num> <newMerge.vmdk>
 -t <num>
  0：寫入文件（容量慢慢增加的）
  1：將硬盤分割切成2GB一個文件
  2：硬盤實際大小（容量為虛擬硬盤大小）
  3：將硬盤分割切成2GB一個文件（總容量為虛擬硬盤大小）
  4：配置成ESX的格式
```

### Manually Install or Upgrade VMware Tools in a Linux Virtual Machine

```bash
ls -l /dev/cdrom
mkdir /mnt/cdrom
mount /dev/cdrom /mnt/cdrom
cd /tmp/
cp -r /mnt/cdrom/ /tmp
ls -l /tmp
umount /dev/cdrom
rm -r /mnt/cdrom
tar zxpf /mnt/cdrom/VMwareTools-10.1.6-5214329.tar.gz
cd vmware-tools-distrib/
./vmware-install.pl
```

### ["VMware Workstation and Device/Credential Guard are not compatible" error in VMware Workstation on Windows 10 host](https://kb.vmware.com/s/article/2146361)

```text
> bcdedit /set hypervisorlaunchtype off
> bcdedit /set hypervisorlaunchtype auto
```

## ESXi

### [CLI](http://xstarcd.github.io/wiki/Cloud/VMWareCLI.html)

```text
vmware -v

esxtop

esxcfg-vmknic -l
esxcfg-route

esxcli hardware cpu list
esxcli hardware cpu global get
esxcli hardware memory get
esxcli hardware platform get
esxcli hardware clock get

esxcli system
esxcli system version get

esxcli network
esxcli network nic list
esxcli network vm list
esxcli network vswitch standard list
esxcli network ip interface ipv4 get
esxcli network ip interface ipv4 set -i vmk0 -I <IP Address> -N <Netmask> -g <Gateway> -t static
esxcli network ip dns server list
esxcli network ip dns server add -s <IP Address>
esxcli network ip dns server remove -s <IP Address>

esxcli vm process list
esxcli vm process kill --type=force --world-id=175134

vim-cmd vmsvc/getallvms
```
