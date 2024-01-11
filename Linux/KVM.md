# [Kernel-based Virtual Machine](https://zh.wikipedia.org/wiki/%E5%9F%BA%E4%BA%8E%E5%86%85%E6%A0%B8%E7%9A%84%E8%99%9A%E6%8B%9F%E6%9C%BA)

- 1. Verify whether your system support Hardware Virtualization
  - VMWare need to enable 'Virtualize Intel-VT-x/EPT or AMD-V/RVI'

```bash
egrep -c '(svm|vmx)' /proc/cpuinfo
apt install cpu-checker -y
kvm-ok
```

- 2. Install KVM(Kernel-based Virtual Machine)

```bash
apt install qemu qemu-kvm libvirt-bin bridge-utils virt-manager -y
```

- 3. Start and Enable libvirtd service

```bash
service --status-all
update-rc.d libvirtd enable
service libvirtd start
service libvirtd status

virsh
virsh list --all
virsh dumpxml generic
```

- 4. Configure Network Bridge for KVM Virtual Machine

```bash
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
```

```bash
networkctl status -a
```

```bash
# vim /etc/default/ufw

DEFAULT_FORWARD_POLICY="ACCEPT"
```

```bash
systemctl restart ufw.service
```

- 5. Creating Virtual Machine

```bash
qemu-system-x86_64 --version
virt-manager
```
