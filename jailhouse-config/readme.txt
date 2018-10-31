
0. Software Components:
    a) linux kernel source (mainline kernel) + 1 patch for libata
    b) jailhouse source (upstream git at github)
    c)  hardware resource description files for root-cell & non-rootcell:
          nuc-7i5d-400MB.c  rt-linux-400MB.c


1. Hardware Configuration

   NUC7i5D + NVMe + SATA SSD,  root cell uses NVMe as rootfs.  And we
   will pass SSD to non-root cell, whose rootfs resides in that SSD.


2. Software
   
   2.1 Root cell
       Linux host system is Ubuntu 18.04 and kernel 4.18.0-xx  (must > 4.7)

   2.2 non-root cell (kernel)
       a) Mainline linux kernel: https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
  
          commit 3a27203102ebfa67bd0bced05b1def499bb59db2 (HEAD -> jailhouse, mainline/master)
          Merge: a24a0eb9c897 4628a64591e6
          Author: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
          Date:   Sun Oct 14 08:34:31 2018 +0200

          Merge tag 'libnvdimm-fixes-4.19-rc8' of git://git.kernel.org/pub/scm/linux/kernel/git/nvdimm/nvdimm
  
       b) apply my patch to mainline linux kernel: 
            0001-Allow-system-to-allocate-IRQ-0-to-ATA-devices.patch
      
         (the patch was sent to linux-ide mailing list)


       c) use kconfig-non-root as .config

    2.3 non-root cell (rootfs)
         I install a ubuntu 18.04 on SSD and use the rootfs 

    
    2.4 Jailhouse:  git clone https://github.com/siemens/jailhouse

                commit f596aa7355bc2134650544bdf1e13f1f55d3f2fc
                Author: Jan Kiszka <jan.kiszka@siemens.com>
                Date:   Mon Sep 24 12:57:19 2018 +0200

                Bump version number


3. Steps to build/try jailhouse
===============================
  3.1 Prepare NUC7i5D, and insert a NVMe disk and a SATA disk, and connect the UART
     of NUC7i5D to your workstation

  3.2 Install Ubunut 18.04 on NVMe of NUC7i5D; and then,

      Add the following into /etc/default/grub:

        GRUB_CMDLINE_LINUX_DEFAULT=" intel_iommu=off memmap=0x400M\\\$0x30000000"

      and then, run "update-grub", reboot;


  3.3 Install ubuntu 18.04 on SATA of NUC7i5D (In fact, we just need a rootfs,
      you can copy rootfs parition from NVMe to SATA, and pay attention to 
      /etc/fstab);

  3.4 Boot into Ubuntu with NVMe;

  3.5 Preapre kernel for non-root cell:
      a) git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
      b) git checkout 3a27203102ebfa67bd0bced05b1def499bb59db2
      c) cp kconfig-non-root linux/.config
      d) git am 0001-Allow-system-to-allocate-IRQ-0-to-ATA-devices.patch
      e) make all; make modules; 

      after this, we get:
           vmlinux-4.19.0-rc7+ and modules-4.19.0-rc

  3.6 Build and install jailhouse on host Ubuntu (NVMe) 
      a) git clone https://github.com/siemens/jailhouse
      b) cp nuc-7i5d-400MB.c  jailhouse/configs/x86/
      c) cp rt-linux-400MB.c  jailhouse/configs/x86/
      d) apt-get install python-pip; pip install mako
      e) make all; make install

      
  3.7 On your workstation open minicom:

        mincom -D /dev/ttyS0 

  3.8  in jailhouse source dir:
       a)  jailhouse enable configs/x86/nuc-7i5d-400MB.cell
       b)  jailhouse cell linux configs/x86/rt-linux-400MB.cell  \
                 bzImage -c "console=ttyS0,115200 root=/dev/sda3"


    Trouble : we expect that login prompt shown in serial console, but it doesn't.
