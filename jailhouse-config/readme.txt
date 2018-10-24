
Hardware NUC7i5D + NVMe + SATA SSD, we will pass SSD to non-root cell

=======================================
For non-root linux:


1. Mainline linux kernel:
  
  commit 3a27203102ebfa67bd0bced05b1def499bb59db2 (HEAD -> jailhouse, mainline/master)
Merge: a24a0eb9c897 4628a64591e6
Author: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Date:   Sun Oct 14 08:34:31 2018 +0200

    Merge tag 'libnvdimm-fixes-4.19-rc8' of git://git.kernel.org/pub/scm/linux/kernel/git/nvdimm/nvdimm
    
2. apply linux-kernel.patch to 1.


3. use kconfig-non-root as .config



====================================


Jailhouse:

1. git clone https://github.com/siemens/jailhouse

   commit f596aa7355bc2134650544bdf1e13f1f55d3f2fc (HEAD -> master, tag: v0.10, origin/master, origin/HEAD)
Author: Jan Kiszka <jan.kiszka@siemens.com>
Date:   Mon Sep 24 12:57:19 2018 +0200

    Bump version number



2. copy nuc-7i5d-sata.c  rt-linux-sata.c  into jailhouse/configs/x86/

3. apt-get install python-pip
   pip install mako

4.  make all


=======================================================
In NUC:
1. vim /etc/default/grub to add:
    GRUB_CMDLINE_LINUX_DEFAULT=" intel_iommu=off memmap=82M\\\$0x3a000000"
  and then, run "update-grub"


2. reboot NUC


3. cd jailhouse
   jailhouse enable configs/x86/nuc-7i5d-sata.cell

4. jailhouse cell linux configs/x86/rt-linux-sata.cell  bzImage -c "console=ttyS0,115200 root=/dev/sda3"
   // assuem that rootfs of non-root cell is in /dev/sda3, which is SATA SSD

~                                                                                                                                













