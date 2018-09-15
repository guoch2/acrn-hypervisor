#!/bin/bash

set -x

mkdir -p /data
mount /dev/nvme0n1p4 /data

function launch_android()
{
if [ ! -f "/data/$5/$5.img" ]; then
  echo "no /data/$5/$5.img, exit"
  exit
fi

#vm-name used to generate uos-mac address
mac=$(cat /sys/class/net/en*/address)
vm_name=vm$1
vm_name=${vm_name}-${mac:9:8}

# create a unique tap device for each VM
tap=tap_AaaG
tap_exist=$(ip a | grep acrn_"$tap" | awk '{print $1}')
if [ "$tap_exist"x != "x" ]; then
  echo "tap device existed, reuse acrn_$tap"
else
  ip tuntap add dev acrn_$tap mode tap
fi

# if acrn-br0 exists, add VM's unique tap device under it
br_exist=$(ip a | grep acrn-br0 | awk '{print $1}')
if [ "$br_exist"x != "x" -a "$tap_exist"x = "x" ]; then
  echo "acrn-br0 bridge aleady exists, adding new tap device to it..."
  ip link set acrn_"$tap" master acrn-br0
  ip link set dev acrn_"$tap" down
  ip link set dev acrn_"$tap" up
fi

#Use MMC name + serial for ADB serial no., same as native android
#mmc_name=`cat /sys/block/mmcblk1/device/name`
#mmc_serial=`cat /sys/block/mmcblk1/device/serial | sed -n 's/^..//p'`
ser=vm1234-cmg

#check if the vm is running or not
vm_ps=$(pgrep -a -f acrn-dm)
result=$(echo $vm_ps | grep "${vm_name}")
if [[ "$result" != "" ]]; then
  echo "$vm_name is running, can't create twice!"
  exit
fi

#if [[ "$vm_name" == "" ]]; then
#echo "should not come here 1"	
#for VT-d device setting
modprobe pci_stub
#if false; then
echo "8086 9d2f" > /sys/bus/pci/drivers/pci-stub/new_id
echo "0000:00:14.0" > /sys/bus/pci/devices/0000:00:14.0/driver/unbind
echo "0000:00:14.0" > /sys/bus/pci/drivers/pci-stub/bind

#echo "8086 9d30" > /sys/bus/pci/drivers/pci-stub/new_id
#echo "0000:00:14.1" > /sys/bus/pci/devices/0000:00:14.1/driver/unbind
#echo "0000:00:14.1" > /sys/bus/pci/drivers/pci-stub/bind
#fi

#echo "8086 15db" > /sys/bus/pci/drivers/pci-stub/new_id
#echo "0000:00:39.0" > /sys/devices/pci0000:00/0000:00:1c.0/0000:01:00.0/0000:02:02.0/0000:39:00.0/driver/unbind
#echo "0000:00:39.0" > /sys/bus/pci/drivers/pci-stub/bind

#echo "8086 15db" > /sys/bus/pci/drivers/pci-stub/new_id
#echo "0000:00:05.0" > /sys/devices/pci0000:02/0000:02:02.0/0000:05:00.0/driver/unbind
#echo "0000:00:05.0" > /sys/bus/pci/drivers/pci-stub/bind

#for audio device
#echo "8086 5a98" > /sys/bus/pci/drivers/pci-stub/new_id
#echo "0000:00:0e.0" > /sys/bus/pci/devices/0000:00:0e.0/driver/unbind
#echo "0000:00:0e.0" > /sys/bus/pci/drivers/pci-stub/bind

#for audio codec
#echo "8086 5ab4" > /sys/bus/pci/drivers/pci-stub/new_id
#echo "0000:00:17.0" > /sys/bus/pci/devices/0000:00:17.0/driver/unbind
#echo "0000:00:17.0" > /sys/bus/pci/drivers/pci-stub/bind

#For CSME passthrough
echo "8086 9d3a" > /sys/bus/pci/drivers/pci-stub/new_id
echo "0000:00:16.0" > /sys/bus/pci/devices/0000:00:16.0/driver/unbind
echo "0000:00:16.0" > /sys/bus/pci/drivers/pci-stub/bind

# for sd card passthrough - SDXC/MMC Host Controller 00:1b.0
#echo "8086 5aca" > /sys/bus/pci/drivers/pci-stub/new_id
#echo "0000:00:1b.0" > /sys/bus/pci/devices/0000:00:1b.0/driver/unbind
#echo "0000:00:1b.0" > /sys/bus/pci/drivers/pci-stub/bind


# WIFI is 4:0.0 on SBL, and 3:0.0 on ABL
#echo "11ab 2b38" > /sys/bus/pci/drivers/pci-stub/new_id
#echo "0000:04:00.0" > /sys/bus/pci/devices/0000:04:00.0/driver/unbind
#echo "0000:04:00.0" > /sys/bus/pci/drivers/pci-stub/bind

# Bluetooth passthrough depends on WIFI
#echo "8086 5abc" > /sys/bus/pci/drivers/pci-stub/new_id
#echo "0000:00:18.0" > /sys/bus/pci/devices/0000:00:18.0/driver/unbind
#echo "0000:00:18.0" > /sys/bus/pci/drivers/pci-stub/bind

boot_ipu_option=""
# for ipu passthrough - ipu device 0:3.0
#if [ -d "/sys/bus/pci/devices/0000:00:03.0" ]; then
#  echo "8086 5a88" > /sys/bus/pci/drivers/pci-stub/new_id
#  echo "0000:00:03.0" > /sys/bus/pci/devices/0000:00:03.0/driver/unbind
#  echo "0000:00:03.0" > /sys/bus/pci/drivers/pci-stub/bind
#  boot_ipu_option="$boot_ipu_option"" -s 12,passthru,0/3/0 "
#fi

# for ipu passthrough - ipu related i2c 0:16.0
# please use virtual slot 22 for i2c 0:16.0 to make sure that the i2c controller
# could get the same virtaul BDF as physical BDF
#if [ -d "/sys/bus/pci/devices/0000:00:16.0" ]; then
#  echo "8086 5aac" > /sys/bus/pci/drivers/pci-stub/new_id
#  echo "0000:00:16.0" > /sys/bus/pci/devices/0000:00:16.0/driver/unbind
#  echo "0000:00:16.0" > /sys/bus/pci/drivers/pci-stub/bind
#  boot_ipu_option="$boot_ipu_option"" -s 22,passthru,0/16/0 "
#fi
#fi

#for memsize setting
memsize=`cat /proc/meminfo|head -n 1|awk '{print $2}'`
if [ $memsize -gt 4000000 ];then
    mem_size=2G
else
    mem_size=1750M
fi

mem_size=2G

if [ "$setup_mem" != "" ];then
    mem_size=$setup_mem
fi

kernel_cmdline_generic="maxcpus=$2 nohpet tsc=reliable intel_iommu=off \
   androidboot.serialno=$ser \
   i915.enable_rc6=1 i915.enable_fbc=1 i915.enable_guc_loading=0 i915.avail_planes_per_pipe=$4 \
   i915.enable_hangcheck=0 use_nuclear_flip=1 i915.enable_initial_modeset=1 i915.enable_guc_submission=0 drm.debug=0x6"

boot_dev_flag=",b"
if [ $6 == 1 ];then
  boot_image_option="--vsbl  /usr/share/acrn/bios/VSBL_debug.bin --enable_trusty"
else
  boot_image_option="--vsbl  /usr/share/acrn/bios/VSBL.bin --enable_trusty"
fi
kernel_cmdline="$kernel_cmdline_generic"

: '
select right virtual slots for acrn_dm:
1. some passthru device need virtual slot same as physical, like audio 0:e.0 at
virtual #14 slot, so "-s 14,passthru,0/e/0"
2. acrn_dm share vioapic irq between some virtual slots: like 6&14, 7&15. Need
guarantee no virt irq sharing for each passthru device.
FIXME: picking a virtual slot (#24 now) which is level-triggered to make sure
audio codec passthrough working
3. the bootable device slot is configured in compile stating in Android Guest
image, it should be kept using 3 as fixed value for Android Guest on Gordon_peak
ACRN project
'
echo 1024 > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages

acrn-dm --help 2>&1 | grep 'GVT args'
if [ $? == 0 ];then
  GVT_args=$3
  boot_GVT_option=" -s 2,pci-gvt -G "
else
  boot_GVT_option=''
  GVT_args=''
fi

 acrn-dm  -A -m $mem_size -c $2 -s 0:0,hostbridge -s 1:0,lpc -l com1,stdio \
   $boot_GVT_option"$GVT_args" \
   -s 9,virtio-net,$tap \
   -s 3,virtio-blk$boot_dev_flag,/data/$5/$5.img \
   -s 11,wdt-i6300esb \
   -s 13,virtio-rpmb \
   -s 7,passthru,0/14/0 \
   -s 10,virtio-hyper_dmabuf \
   -s 16,passthru,0/16/0 \
   $boot_image_option \
   -B "$kernel_cmdline" $vm_name

   #$boot_GVT_option"$GVT_args" \
   #-s 14,passthru,0/e/0,keep_gsi \
   #-s 15,passthru,0/f/0 \
   #-s 27,passthru,0/1b/0 \
   #-s 24,passthru,0/18/0 \
   #-s 18,passthru,4/0/0,keep_gsi \
   #-s 20,passthru,0/5/0 \
   #-s 21,passthru,0/39/0 \
   #-s 23,passthru,0/17/0 \
   #-s 8,passthru,0/14/1 \

}

function help()
{
echo "Use luanch_uos.sh like that ./launch_uos.sh -V <#>"
echo "The option -V means the UOSs group to be launched by vsbl as below"
echo "-V 1 means just launching 1 clearlinux UOS"
echo "-V 2 means just launching 1 android UOS"
echo "-V 3 means launching 1 clearlinux UOS + 1 android UOS"
echo "-V 4 means launching 2 clearlinux UOSs"
}

debug=0

while getopts "V:M:hd" opt
do
	case $opt in
		V) launch_type=$[$OPTARG]
			;;
		M) setup_mem=$OPTARG
			;;
		d) debug=1
			;;
		h) help
			exit 1
			;;
		?) help
			exit 1
			;;
	esac
done

#mkdir -p /data
#mount /dev/mmcblk1p3 /data

# make sure there is enough 2M hugepages in the pool
#echo 1024 > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
#echo 900 > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages

echo 0xF >/sys/kernel/debug/dri/0/i915_gem_drop_caches

for i in `ls -d /sys/devices/system/cpu/cpu[1-99]`; do
        online=`cat $i/online`
        idx=`echo $i | tr -cd "[1-99]"`
        echo cpu$idx online=$online
        if [ "$online" = "1" ]; then
                echo 0 > $i/online
                echo $idx > /sys/class/vhm/acrn_vhm/offline_cpu
        fi
done

case $launch_type in
	1) echo "Launch clearlinux UOS"
		launch_clearlinux 1 1 "64 448 8" 0x070F00 clearlinux $debug
		;;
	2) echo "Launch android UOS"
		#Use below line when i915.enable_initial_modeset=1
		#launch_android 1 1 "64 448 8" 0x070F00 android $debug
		launch_android 1 1 "64 448 8" 0x070F00 android $debug
		#Use below line when i915.enable_initial_modeset=0
		#launch_android 1 1 "64 448 8" 0 android $debug
		#####JiangFei's SOS hang workaround
		#launch_android 1 1 "64 448 8" 0 android $debug
		;;
	3) echo "Launch clearlinux UOS + android UOS"
		launch_android 1 2 "64 448 4" 0x00000C android $debug &
		sleep 5
		launch_clearlinux 2 1 "64 448 4" 0x070F00 clearlinux $debug
		;;
	4) echo "Launch two clearlinux UOSs"
		launch_clearlinux 1 1 "64 448 4" 0x00000C clearlinux $debug &
		sleep 5
		launch_clearlinux 2 1 "64 448 4" 0x070F00 clearlinux_dup $debug
		;;
esac

#umount /data
