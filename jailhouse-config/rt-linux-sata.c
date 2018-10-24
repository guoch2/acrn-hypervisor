/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Minimal configuration for demo inmates, 1 CPU, 1 MB RAM, serial ports
 *
 * Copyright (c) Siemens AG, 2013, 2014
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

struct {
	struct jailhouse_cell_desc cell;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[7];
	__u8 pio_bitmap[0x2000];
	struct jailhouse_pci_device pci_devices[2];
	struct jailhouse_pci_capability pci_caps[3];
} __attribute__((packed)) config = {
	.cell = {
		.signature = JAILHOUSE_CELL_DESC_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.name = "rt-linux",
		.flags = JAILHOUSE_CELL_PASSIVE_COMMREG |
			JAILHOUSE_CELL_VIRTUAL_CONSOLE_PERMITTED,

		.cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.pio_bitmap_size = ARRAY_SIZE(config.pio_bitmap),
		.num_pci_devices = ARRAY_SIZE(config.pci_devices),
		.num_pci_caps = ARRAY_SIZE(config.pci_caps),

	},

	.cpus = {
		0xc,
	},

	.mem_regions = {
		/* Low RAM */ {
			.phys_start = 0x3a600000,
			.virt_start = 0,
			.size = 0x00100000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA |
				JAILHOUSE_MEM_LOADABLE,

		},
		/* communication region */ {
			.virt_start = 0x00100000,
			.size = 0x00001000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_COMM_REGION,
		},
		/* high RAM */ {
			.phys_start = 0x3a700000,
			.virt_start = 0x00200000,
			.size = 0x04a00000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA |
				JAILHOUSE_MEM_LOADABLE,
		},
		/* communication region */ {
			.phys_start = 0x3f100000,
			.virt_start = 0x3f100000,
			.size = 0x000ff000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_ROOTSHARED

		},

		/* MemRegion: df248000-df249fff : ahci */
		{
			.phys_start = 0xdf248000,
			.virt_start = 0xdf248000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: df24b000-df24b7ff : ahci */
		{
			.phys_start = 0xdf24b000,
			.virt_start = 0xdf24b000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: df24c000-df24c0ff : ahci */
		{
			.phys_start = 0xdf24c000,
			.virt_start = 0xdf24c000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_DMA,
		},

	},

# if 0
	.pio_bitmap = {
		[   0x0/8 ...  0x1ff/8] = -1,
		[ 0x200/8 ...  0x2f7/8] = 0,
		[ 0x2f8/8 ...  0x2ff/8] = 0, /* serial2 */
		[ 0x300/8 ...  0x3f7/8] = 0, 
		[ 0x3f8/8 ...  0x3ff/8] = 0, /* serial1 */
		[ 0x400/8 ... 0xdfff/8] = -1,
		[0xe000/8 ... 0xe007/8] = 0, /* OXPCIe952 serial2 */
		[0xe008/8 ... 0xffff/8] = 0,
	},

#endif

	.pio_bitmap = {
		[   0x0/8 ...   0x1f/8] = -1,    /* dma1 */
		[  0x20/8 ...   0x2f/8] = 0,    /* pic1 */
		[  0x30/8 ...   0x3f/8] = -1,  
		[  0x40/8 ...   0x5f/8] = -1,  /*  timer0/1 */
		[  0x60/8 ...   0x6f/8] = -1,  /* kbd, pnp ec */
		[  0x70/8 ...   0x7f/8] = -1,  /* rtc */
		[  0x80/8 ...   0x8f/8] = -1,  /* dma page reg */
		[  0x90/8 ...  0x1ff/8] = -1,  
		[ 0x200/8 ...  0x2d7/8] = -1,
		[ 0x2e0/8 ...  0x2ef/8] = 0,  /* who is acessing this ??? */ 
		[ 0x2f0/8 ...  0x2f7/8] = -1,
		[ 0x2f8/8 ...  0x2ff/8] = 0, /* serial2 */
		[ 0x300/8 ...  0x3df/8] = -1, 
		[ 0x3e0/8 ...  0x3ef/8] = 0,   /* who is access this port ??? */
		[ 0x3f0/8 ...  0x3f7/8] = -1, 
		[ 0x3f8/8 ...  0x3ff/8] = 0, /* serial1 */
		[ 0x400/8 ... 0xdfff/8] = -1,
		[0xe000/8 ... 0xe007/8] = -1, /* OXPCIe952 serial2 */
		[0xe008/8 ... 0xf05f/8] = -1, 
		[0xf060/8 ... 0xf09f/8] = 0,
		[0xf0a0/8 ... 0xffff/8] = -1,
	},

	.pci_devices = {
		{
			.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
			.domain = 0x0,
			.bdf = 0x10 << 3,
			.bar_mask = {
				0xffffff00, 0xffffffff, 0x00000000,
				0x00000000, 0xffffffe0, 0xffffffff,
			},
			.num_msix_vectors = 1,
			.shmem_region = 3,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_VETH,
		},
		/* PCIDevice: 00:17.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xb8,
			.bar_mask = {
				0xffffe000, 0xffffff00, 0xfffffff8,
				0xfffffffc, 0xffffffe0, 0xfffff800,
			},
			.caps_start = 0,
			.num_caps = 3,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
	},

	.pci_caps = {
		/* PCIDevice: 00:17.0 */
		{
			.id = 0x5,
			.start = 0x80,
			.len = 10,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x1,
			.start = 0x70,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x12,
			.start = 0xa8,
			.len = 2,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
	}
};
