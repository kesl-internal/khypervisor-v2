#ifndef __CONFIG_H__
#define __CONFIG_H__

#define MACHINE_TYPE            4283
#define CFG_CNTFRQ              24000000

#define HYP_STACK_SIZE          8192
#define NR_CPUS                 2
#define BOOTABLE_CPUID          (0 << 8)

/*
 *  SOC param
 */
#define CFG_GIC_BASE_PA     0x01c80000
#define CFG_GICD_BASE_PA    0x01c81000
#define CFG_GICC_BASE_PA    0x01c82000

#define NSEC_DIV 1000000000
#define TIMER_RESOLUTION_NS (NSEC_DIV/CFG_CNTFRQ)

#define MAX_IRQS 1024

#define CFG_MEMMAP_GUEST_SIZE               0x10000000

#define CFG_MEMMAP_GUEST0_ATAGS_OFFSET      0x48000000
#define CFG_MEMMAP_GUEST0_OFFSET            0x48000000

#define CFG_MEMMAP_GUEST1_ATAGS_OFFSET      0x58000000
#define CFG_MEMMAP_GUEST1_OFFSET            0x58000000

#define CFG_MEMMAP_GUEST2_ATAGS_OFFSET      0x68000000
#define CFG_MEMMAP_GUEST2_OFFSET            0x68000000

#define CFG_GUEST_ATAGS_START_ADDRESS       0x48000000

#define CFG_GUEST_START_ADDRESS             0x48000000

#define CFG_HYP_START_ADDRESS               0xb0000000


#endif  /* BANANAPI_CONFIG_H */