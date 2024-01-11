# Linux Kernel Module

```bash
# ls -l /usr/src

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
```

## [WSL2-Linux-Kernel](https://github.com/microsoft/WSL2-Linux-Kernel)

```bash
# uname -r
5.10.16.3-microsoft-standard-WSL2
```

```bash
cd /opt
git clone https://github.com/microsoft/WSL2-Linux-Kernel.git
git checkout linux-msft-wsl-5.10.16.3
wget https://github.com/microsoft/WSL2-Linux-Kernel/archive/refs/tags/linux-msft-wsl-5.10.16.3.tar.gz

cd WSL2-Linux-Kernel
cp Microsoft/config-wsl .config
make oldconfig
make prepare
make scripts
make modules
make modules_install
```

```bash
# ls -l /lib/modules/5.10.16.3-microsoft-standard-WSL2+
# ls -l /lib/modules/5.10.16.3-microsoft-standard-WSL2+/build

KERNEL_DIR = /lib/modules/5.10.16.3-microsoft-standard-WSL2+/build
```

## compiling by getting another kernel

```bash
apt-cache search linux-headers
apt install linux-headers-$(uname -r)
apt install linux-generic -y
dpkg -l | grep linux
dpkg -L linux-headers-5.4.0-97-generic | grep "/lib/modules"
```

```bash
# ls -l /lib/modules
# ls -l /lib/modules/5.4.0-97-generic
# ls -l /lib/modules/5.4.0-97-generic/build

KERNEL_DIR = /lib/modules/5.4.0-97-generic/build
```

## Example

- vim hello.c

```c
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void) {
    printk(KERN_INFO "Hello, Kernel.\n");

    return 0;
}

static void hello_exit(void) { printk(KERN_INFO "Goodbye, Kernel.\n"); }

module_init(hello_init);
module_exit(hello_exit);
```

- vim Makefile

```makefile
PWD = $(shell pwd)
KERNEL_DIR = /lib/modules/$(shell uname -r)/build
# KERNEL_DIR = /lib/modules/5.10.16.3-microsoft-standard-WSL2+/build
# KERNEL_DIR = /lib/modules/5.4.0-97-generic/build
MODULE_NAME = hello
obj-m = $(MODULE_NAME).o

all: clean
    make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
    make -C $(KERNEL_DIR) M=$(PWD) clean
```

```bash
make
modinfo hello.ko

insmod hello.ko
lsmod | grep hello
dmesg

rmmod hello
lsmod | grep hello
dmesg
```
