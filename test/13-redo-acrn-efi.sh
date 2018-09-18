#!/bin/bash

ACRN_IMAGE=`ls out/acrn_vdisk_clear*`


make -C acrn-hypervisor hypervisor

[ ! -f ${ACRN_IMAGE} ] && { echo "Failed to find acrn image in `pwd`"; exit 1; }

echo "update ${ACRN_IMAGE} ..."

guestmount -a ${ACRN_IMAGE}  -m /dev/sda1 /mnt

cp  acrn-hypervisor/build/hypervisor/acrn.efi /mnt/EFI/BOOT/BOOTX64.EFI

cp  acrn-hypervisor/build/hypervisor/acrn.efi /mnt/EFI/org.clearlinux/acrn.efi

sync

guestunmount /mnt/


echo "updated ${ACRN_IMAGE} !!!, try to run 11-acrn-in-qemu-ovmf.sh to verify the image."
