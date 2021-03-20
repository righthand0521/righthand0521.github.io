Virtualization
===
### VMware Workstation
### How to merge multiple vmdk’s into single vmdk
```
"C:\Program Files (x86)\VMware\VMware Workstation\vmware-vdiskmanager.exe" -r <original.vmdk> -t <num> <newMerge.vmdk>
 -t <num>
  0：寫入文件（容量慢慢增加的）
  1：將硬盤分割切成2GB一個文件
  2：硬盤實際大小（容量為虛擬硬盤大小）
  3：將硬盤分割切成2GB一個文件（總容量為虛擬硬盤大小）
  4：配置成ESX的格式
```
### Manually Install or Upgrade VMware Tools in a Linux Virtual Machine
```
# ls -l /dev/cdrom
# mkdir /mnt/cdrom
# mount /dev/cdrom /mnt/cdrom
# cd /tmp/
# cp -r /mnt/cdrom/ /tmp
# ls -l /tmp
# umount /dev/cdrom
# rm -r /mnt/cdrom
# tar zxpf /mnt/cdrom/VMwareTools-10.1.6-5214329.tar.gz
# cd vmware-tools-distrib/
# ./vmware-install.pl
```
### ["VMware Workstation and Device/Credential Guard are not compatible" error in VMware Workstation on Windows 10 host](https://kb.vmware.com/s/article/2146361)
```
> bcdedit /set hypervisorlaunchtype off
> bcdedit /set hypervisorlaunchtype auto
```
---
### VMware ESXi
### [CLI](http://xstarcd.github.io/wiki/Cloud/VMWareCLI.html)
```
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
---
### VirtualBox
```
"C:\Program Files\Oracle\VirtualBox\VBoxManage.exe" clonehd "<fileName>.vdi" "<fileName>.vmdk" --format VMDK
```
---
### [Kernel-based Virtual Machine](https://zh.wikipedia.org/wiki/%E5%9F%BA%E4%BA%8E%E5%86%85%E6%A0%B8%E7%9A%84%E8%99%9A%E6%8B%9F%E6%9C%BA)
```
1. Verify whether your system support Hardware Virtualization

VMWare need to enable 'Virtualize Intel-VT-x/EPT or AMD-V/RVI'
# egrep -c '(svm|vmx)' /proc/cpuinfo
# apt install cpu-checker
# kvm-ok
```
```
2. Install KVM(Kernel-based Virtual Machine)

# apt install qemu qemu-kvm libvirt-bin bridge-utils virt-manager -y
```
```
3. Start and Enable libvirtd service

# service --status-all
# update-rc.d libvirtd enable
# service libvirtd start
# service libvirtd status

# virsh
# virsh list --all
# virsh dumpxml generic
```
```
4. Configure Network Bridge for KVM Virtual Machine

# vim /etc/network/interfaces
auto lo
iface lo inet loopback
auto eth0
auto br0
iface br0 inet static
address 192.168.0.1
netmask 255.255.255.0
gateway 192.168.0.254
dns-nameservers 8.8.8.8
bridge_ports eth0
bridge_stp on
bridge_fd 0

# networkctl status -a

# vim /etc/default/ufw
DEFAULT_FORWARD_POLICY="ACCEPT"

# systemctl restart ufw.service
```
```
5. Creating Virtual Machine

# qemu-system-x86_64 --version
# virt-manager
```
---
