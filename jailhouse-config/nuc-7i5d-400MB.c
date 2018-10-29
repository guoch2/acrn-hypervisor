/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2014-2017
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * Alternatively, you can use or redistribute this file under the following
 * BSD license:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Configuration for Intel Corporation NUC7i5DNHE
 * created with '/usr/local/libexec/jailhouse/jailhouse config create --mem-hv 6M --mem-inmates 944M t.c'
 *
 * NOTE: This config expects the following to be appended to your kernel cmdline
 *       "memmap=0x40000000$0x30000000"
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

struct {
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[61];
	struct jailhouse_irqchip irqchips[1];
	__u8 pio_bitmap[0x2000];
	struct jailhouse_pci_device pci_devices[19];
	struct jailhouse_pci_capability pci_caps[52];
} __attribute__((packed)) config = {
	.header = {
		.signature = JAILHOUSE_SYSTEM_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.flags = JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE,
		.hypervisor_memory = {
			.phys_start = 0x30000000,
			.size = 0x600000,
		},
		.debug_console = {
			.address = 0x3f8,
			.divider = 0x1,   /* 115200 */
			.type = JAILHOUSE_CON_TYPE_8250,
			.flags = JAILHOUSE_CON_ACCESS_PIO |
				 JAILHOUSE_CON_REGDIST_1,
		},
		.platform_info = {
			.pci_mmconfig_base = 0xe0000000,
			.pci_mmconfig_end_bus = 0xff,
			.x86 = {
				.pm_timer_address = 0x1808,
				.vtd_interrupt_limit = 256,
				.iommu_units = {
					{
						.base = 0xfed90000,
						.size = 0x1000,
					},
					{
						.base = 0xfed91000,
						.size = 0x1000,
					},
				},
			},
		},
		.root_cell = {
			.name = "RootCell",
			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
			.num_irqchips = ARRAY_SIZE(config.irqchips),
			.pio_bitmap_size = ARRAY_SIZE(config.pio_bitmap),
			.num_pci_devices = ARRAY_SIZE(config.pci_devices),
			.num_pci_caps = ARRAY_SIZE(config.pci_caps),
		},
	},

	.cpus = {
		0x000000000000000f,
	},

	.mem_regions = {
		/* MemRegion: 00000000-00057fff : System RAM */
		{
			.phys_start = 0x0,
			.virt_start = 0x0,
			.size = 0x58000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 00059000-0009dfff : System RAM */
		{
			.phys_start = 0x59000,
			.virt_start = 0x59000,
			.size = 0x45000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 00100000-2fffffff : System RAM */
		{
			.phys_start = 0x100000,
			.virt_start = 0x100000,
			.size = 0x2ff00000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 70000000-779aafff : System RAM */
		{
			.phys_start = 0x70000000,
			.virt_start = 0x70000000,
			.size = 0x79ab000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 779ab000-779abfff : ACPI Non-volatile Storage */
		{
			.phys_start = 0x779ab000,
			.virt_start = 0x779ab000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 779ad000-7f58bfff : System RAM */
		{
			.phys_start = 0x779ad000,
			.virt_start = 0x779ad000,
			.size = 0x7bdf000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 7fa1c000-7fa64fff : ACPI Tables */
		{
			.phys_start = 0x7fa1c000,
			.virt_start = 0x7fa1c000,
			.size = 0x49000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 7fa65000-7fac4fff : ACPI Non-volatile Storage */
		{
			.phys_start = 0x7fa65000,
			.virt_start = 0x7fa65000,
			.size = 0x60000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 7ff2d000-7fffefff : Unknown E820 type */
		{
			.phys_start = 0x7ff2d000,
			.virt_start = 0x7ff2d000,
			.size = 0xd2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 7ffff000-7fffffff : System RAM */
		{
			.phys_start = 0x7ffff000,
			.virt_start = 0x7ffff000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: c0000000-cfffffff : 0000:00:02.0 */
		{
			.phys_start = 0xc0000000,
			.virt_start = 0xc0000000,
			.size = 0x10000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: de000000-deffffff : 0000:00:02.0 */
		{
			.phys_start = 0xde000000,
			.virt_start = 0xde000000,
			.size = 0x1000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df000000-df001fff : nvme */
		{
			.phys_start = 0xdf000000,
			.virt_start = 0xdf000000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df003000-df003fff : nvme */
		{
			.phys_start = 0xdf003000,
			.virt_start = 0xdf003000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df100000-df101fff : iwlwifi */
		{
			.phys_start = 0xdf100000,
			.virt_start = 0xdf100000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df200000-df21ffff : e1000e */
		{
			.phys_start = 0xdf200000,
			.virt_start = 0xdf200000,
			.size = 0x20000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df220000-df22ffff : ICH HD audio */
		{
			.phys_start = 0xdf220000,
			.virt_start = 0xdf220000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df230000-df23ffff : xhci-hcd */
		{
			.phys_start = 0xdf230000,
			.virt_start = 0xdf230000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df240000-df243fff : ICH HD audio */
		{
			.phys_start = 0xdf240000,
			.virt_start = 0xdf240000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df244000-df247fff : 0000:00:1f.2 */
		{
			.phys_start = 0xdf244000,
			.virt_start = 0xdf244000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df248000-df249fff : ahci */
		{
			.phys_start = 0xdf248000,
			.virt_start = 0xdf248000,
			.size = 0x2000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df24a000-df24a0ff : 0000:00:1f.4 */
		{
			.phys_start = 0xdf24a000,
			.virt_start = 0xdf24a000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df24b000-df24b7ff : ahci */
		{
			.phys_start = 0xdf24b000,
			.virt_start = 0xdf24b000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df24c000-df24c0ff : ahci */
		{
			.phys_start = 0xdf24c000,
			.virt_start = 0xdf24c000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df24d000-df24dfff : 0000:00:16.3 */
		{
			.phys_start = 0xdf24d000,
			.virt_start = 0xdf24d000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df24e000-df24efff : mei_me */
		{
			.phys_start = 0xdf24e000,
			.virt_start = 0xdf24e000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df24f000-df24f1ff : lpss_dev */
		{
			.phys_start = 0xdf24f000,
			.virt_start = 0xdf24f000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df24f200-df24f2ff : lpss_priv */
		{
			.phys_start = 0xdf24f200,
			.virt_start = 0xdf24f200,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df24f800-df24ffff : idma64.1 */
		{
			.phys_start = 0xdf24f800,
			.virt_start = 0xdf24f800,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df250000-df2501ff : lpss_dev */
		{
			.phys_start = 0xdf250000,
			.virt_start = 0xdf250000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df250200-df2502ff : lpss_priv */
		{
			.phys_start = 0xdf250200,
			.virt_start = 0xdf250200,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df250800-df250fff : idma64.0 */
		{
			.phys_start = 0xdf250800,
			.virt_start = 0xdf250800,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df251000-df251fff : Intel PCH thermal driver */
		{
			.phys_start = 0xdf251000,
			.virt_start = 0xdf251000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: df252000-df252fff : 0000:00:08.0 */
		{
			.phys_start = 0xdf252000,
			.virt_start = 0xdf252000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: dffe0000-dfffffff : pnp 00:05 */
		{
			.phys_start = 0xdffe0000,
			.virt_start = 0xdffe0000,
			.size = 0x20000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fd000000-fdabffff : pnp 00:06 */
		{
			.phys_start = 0xfd000000,
			.virt_start = 0xfd000000,
			.size = 0xac0000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fdac0000-fdacffff : INT344B:00 */
		{
			.phys_start = 0xfdac0000,
			.virt_start = 0xfdac0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fdad0000-fdadffff : pnp 00:06 */
		{
			.phys_start = 0xfdad0000,
			.virt_start = 0xfdad0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fdae0000-fdaeffff : INT344B:00 */
		{
			.phys_start = 0xfdae0000,
			.virt_start = 0xfdae0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fdaf0000-fdafffff : INT344B:00 */
		{
			.phys_start = 0xfdaf0000,
			.virt_start = 0xfdaf0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fdc6000c-fdc6000f : wdat_wdt */
		{
			.phys_start = 0xfdc6000c,
			.virt_start = 0xfdc6000c,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fe028000-fe028fff : pnp 00:08 */
		{
			.phys_start = 0xfe028000,
			.virt_start = 0xfe028000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fe029000-fe029fff : pnp 00:08 */
		{
			.phys_start = 0xfe029000,
			.virt_start = 0xfe029000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fe036000-fe03bfff : pnp 00:06 */
		{
			.phys_start = 0xfe036000,
			.virt_start = 0xfe036000,
			.size = 0x6000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fe03d000-fe3fffff : pnp 00:06 */
		{
			.phys_start = 0xfe03d000,
			.virt_start = 0xfe03d000,
			.size = 0x3c3000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fe410000-fe7fffff : pnp 00:06 */
		{
			.phys_start = 0xfe410000,
			.virt_start = 0xfe410000,
			.size = 0x3f0000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed00000-fed003ff : HPET 0 */
		{
			.phys_start = 0xfed00000,
			.virt_start = 0xfed00000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed10000-fed17fff : pnp 00:05 */
		{
			.phys_start = 0xfed10000,
			.virt_start = 0xfed10000,
			.size = 0x8000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed18000-fed18fff : pnp 00:05 */
		{
			.phys_start = 0xfed18000,
			.virt_start = 0xfed18000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed19000-fed19fff : pnp 00:05 */
		{
			.phys_start = 0xfed19000,
			.virt_start = 0xfed19000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed20000-fed3ffff : pnp 00:05 */
		{
			.phys_start = 0xfed20000,
			.virt_start = 0xfed20000,
			.size = 0x20000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed40000-fed44fff : MSFT0101:00 */
		{
			.phys_start = 0xfed40000,
			.virt_start = 0xfed40000,
			.size = 0x5000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fed45000-fed8ffff : pnp 00:05 */
		{
			.phys_start = 0xfed45000,
			.virt_start = 0xfed45000,
			.size = 0x4b000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: 100000000-224bfffff : System RAM */
		{
			.phys_start = 0x100000000,
			.virt_start = 0x100000000,
			.size = 0x124c00000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 224c00000-226ffffff : Kernel */
		{
			.phys_start = 0x224c00000,
			.virt_start = 0x224c00000,
			.size = 0x2400000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 227000000-270ffffff : System RAM */
		{
			.phys_start = 0x227000000,
			.virt_start = 0x227000000,
			.size = 0x4a000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 271000000-273ffffff : RAM buffer */
		{
			.phys_start = 0x271000000,
			.virt_start = 0x271000000,
			.size = 0x3000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 7f99d000-7f9bcfff : ACPI DMAR RMRR */
		/* PCI device: 00:14.0 */
		{
			.phys_start = 0x7f99d000,
			.virt_start = 0x7f99d000,
			.size = 0x20000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 88800000-8cffffff : ACPI DMAR RMRR */
		/* PCI device: 00:02.0 */
		{
			.phys_start = 0x88800000,
			.virt_start = 0x88800000,
			.size = 0x4800000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_DMA,
		},
		/* MemRegion: 30600000-6b5fffff : JAILHOUSE Inmate Memory */
		{
			.phys_start = 0x30600000,
			.virt_start = 0x30600000,
			.size = 0x3b000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* ISVHMEM MemRegion: 6b5fffff : JAILHOUSE Memory */
		{
			.phys_start = 0x6b600000,
			.virt_start = 0x6b600000,
			.size = 0xff000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
	},

	.irqchips = {
		/* IOAPIC 2, GSI base 0 */
		{
			.address = 0xfec00000,
			.id = 0x1f0f8,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
	},

	.pio_bitmap = {
		[     0/8 ...   0x3f/8] = -1,
		[  0x40/8 ...   0x47/8] = 0xf0, /* PIT */
		[  0x48/8 ...   0x5f/8] = -1,
		[  0x60/8 ...   0x67/8] = 0xec, /* HACK: NMI status/control */
		[  0x68/8 ...   0x6f/8] = -1,
		[  0x70/8 ...   0x77/8] = 0xfc, /* RTC */
		[  0x78/8 ...  0x3af/8] = -1,
		[ 0x3b0/8 ...  0x3df/8] = 0x00, /* VGA */
		[ 0x3e0/8 ...  0x3f7/8] = -1,
		[ 0x3f8/8 ...  0x3ff/8] = 0,  /* UART0 */
		[ 0x400/8 ...  0xcff/8] = -1,
		[ 0xd00/8 ... 0xffff/8] = 0, /* HACK: PCI bus */
	},

	.pci_devices = {
		/* PCIDevice: 00:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x0,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 1,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:02.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 0,
			.domain = 0x0,
			.bdf = 0x10,
			.bar_mask = {
				0xff000000, 0xffffffff, 0xf0000000,
				0xffffffff, 0xffffffc0, 0x00000000,
			},
			.caps_start = 1,
			.num_caps = 7,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:08.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x40,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 8,
			.num_caps = 3,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:14.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xa0,
			.bar_mask = {
				0xffff0000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 11,
			.num_caps = 2,
			.num_msi_vectors = 8,
			.msi_64bits = 1,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:14.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xa2,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 13,
			.num_caps = 2,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:15.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xa8,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 15,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:15.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xa9,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 15,
			.num_caps = 2,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:16.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xb0,
			.bar_mask = {
				0xfffff000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 17,
			.num_caps = 2,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:16.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xb3,
			.bar_mask = {
				0xfffffff8, 0xfffff000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 19,
			.num_caps = 2,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
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
			.caps_start = 21,
			.num_caps = 3,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1c.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xe0,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 24,
			.num_caps = 8,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1d.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_BRIDGE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xe8,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 24,
			.num_caps = 8,
			.num_msi_vectors = 1,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xf8,
			.bar_mask = {
				0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xfa,
			.bar_mask = {
				0xffffc000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.3 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xfb,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0xffff0000, 0xffffffff,
			},
			.caps_start = 32,
			.num_caps = 2,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.4 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xfc,
			.bar_mask = {
				0xffffff00, 0xffffffff, 0x00000000,
				0x00000000, 0xffffffe0, 0x00000000,
			},
			.caps_start = 0,
			.num_caps = 0,
			.num_msi_vectors = 0,
			.msi_64bits = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 00:1f.6 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0xfe,
			.bar_mask = {
				0xfffe0000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 34,
			.num_caps = 3,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 01:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x100,
			.bar_mask = {
				0xffffe000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 37,
			.num_caps = 7,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 02:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x200,
			.bar_mask = {
				0xffffc000, 0xffffffff, 0x00000000,
				0x00000000, 0x00000000, 0x00000000,
			},
			.caps_start = 44,
			.num_caps = 8,
			.num_msi_vectors = 8,
			.msi_64bits = 1,
			.num_msix_vectors = 16,
			.msix_region_size = 0x1000,
			.msix_address = 0xdf002000,
		},
	},

	.pci_caps = {
		/* PCIDevice: 00:00.0 */
		{
			.id = 0x9,
			.start = 0xe0,
			.len = 2,
			.flags = 0,
		},
		/* PCIDevice: 00:02.0 */
		{
			.id = 0x9,
			.start = 0x40,
			.len = 2,
			.flags = 0,
		},
		{
			.id = 0x10,
			.start = 0x70,
			.len = 60,
			.flags = 0,
		},
		{
			.id = 0x5,
			.start = 0xac,
			.len = 10,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x1,
			.start = 0xd0,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x1b | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 4,
			.flags = 0,
		},
		{
			.id = 0xf | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x200,
			.len = 4,
			.flags = 0,
		},
		{
			.id = 0x13 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x300,
			.len = 4,
			.flags = 0,
		},
		/* PCIDevice: 00:08.0 */
		{
			.id = 0x5,
			.start = 0x90,
			.len = 10,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x1,
			.start = 0xdc,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x13,
			.start = 0xf0,
			.len = 2,
			.flags = 0,
		},
		/* PCIDevice: 00:14.0 */
		{
			.id = 0x1,
			.start = 0x70,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x5,
			.start = 0x80,
			.len = 14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* PCIDevice: 00:14.2 */
		{
			.id = 0x1,
			.start = 0x50,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x5,
			.start = 0x80,
			.len = 10,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* PCIDevice: 00:15.0 */
		/* PCIDevice: 00:15.1 */
		{
			.id = 0x1,
			.start = 0x80,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x9,
			.start = 0x90,
			.len = 2,
			.flags = 0,
		},
		/* PCIDevice: 00:16.0 */
		{
			.id = 0x1,
			.start = 0x50,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x5,
			.start = 0x8c,
			.len = 14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* PCIDevice: 00:16.3 */
		{
			.id = 0x5,
			.start = 0x40,
			.len = 14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x1,
			.start = 0x50,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
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
			.flags = 0,
		},
		/* PCIDevice: 00:1c.0 */
		/* PCIDevice: 00:1d.0 */
		{
			.id = 0x10,
			.start = 0x40,
			.len = 60,
			.flags = 0,
		},
		{
			.id = 0x5,
			.start = 0x80,
			.len = 10,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0xd,
			.start = 0x90,
			.len = 2,
			.flags = 0,
		},
		{
			.id = 0x1,
			.start = 0xa0,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x1 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 4,
			.flags = 0,
		},
		{
			.id = 0xd | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x140,
			.len = 4,
			.flags = 0,
		},
		{
			.id = 0x1e | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x200,
			.len = 4,
			.flags = 0,
		},
		{
			.id = 0x19 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x220,
			.len = 4,
			.flags = 0,
		},
		/* PCIDevice: 00:1f.3 */
		{
			.id = 0x1,
			.start = 0x50,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x5,
			.start = 0x60,
			.len = 14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		/* PCIDevice: 00:1f.6 */
		{
			.id = 0x1,
			.start = 0xc8,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x5,
			.start = 0xd0,
			.len = 14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x13,
			.start = 0xe0,
			.len = 2,
			.flags = 0,
		},
		/* PCIDevice: 01:00.0 */
		{
			.id = 0x1,
			.start = 0xc8,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x5,
			.start = 0xd0,
			.len = 14,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x10,
			.start = 0x40,
			.len = 60,
			.flags = 0,
		},
		{
			.id = 0x1 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 4,
			.flags = 0,
		},
		{
			.id = 0x3 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x140,
			.len = 4,
			.flags = 0,
		},
		{
			.id = 0x18 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x14c,
			.len = 4,
			.flags = 0,
		},
		{
			.id = 0x1e | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x154,
			.len = 4,
			.flags = 0,
		},
		/* PCIDevice: 02:00.0 */
		{
			.id = 0x1,
			.start = 0x40,
			.len = 8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x5,
			.start = 0x50,
			.len = 24,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x10,
			.start = 0x70,
			.len = 60,
			.flags = 0,
		},
		{
			.id = 0x11,
			.start = 0xb0,
			.len = 12,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = 0x1 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 4,
			.flags = 0,
		},
		{
			.id = 0x19 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x158,
			.len = 4,
			.flags = 0,
		},
		{
			.id = 0x18 | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x178,
			.len = 4,
			.flags = 0,
		},
		{
			.id = 0x1e | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x180,
			.len = 4,
			.flags = 0,
		},
	},
};
