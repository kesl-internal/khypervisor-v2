#ifndef __CONFIG_H__
#define __CONFIG_H__

#define MAHINE_TYPE             4538
#define CFG_CNTFRQ              100000000

#define HYP_STACK_SIZE          4096
#define NR_CPUS                 2
#define NUM_GUESTS_STATIC       3

/*
 *  SOC param
 */
#define CFG_GIC_BASE_PA     0xF1000000
#define CFG_GICD_BASE_PA    0xF1001000
#define CFG_GICC_BASE_PA    0xF1002000

#define NSEC_DIV 1000000000
#define TIMER_RESOLUTION_NS (NSEC_DIV/CFG_CNTFRQ)

#define NUM_GUESTS_CPU0_STATIC       2
#define MAX_IRQS 1024

#define CFG_MEMMAP_GUEST_SIZE				0x00100000

#define CFG_MEMMAP_GUEST0_ATAGS_OFFSET      0x40000000
#define CFG_MEMMAP_GUEST0_OFFSET            0x40500000

#define CFG_MEMMAP_GUEST1_ATAGS_OFFSET      0x50000000
#define CFG_MEMMAP_GUEST1_OFFSET            0x50500000

#define CFG_MEMMAP_GUEST2_ATAGS_OFFSET      0x60000000
#define CFG_MEMMAP_GUEST2_OFFSET            0x60500000

#define CFG_GUEST_ATAGS_START_ADDRESS       0x40500000

#define CFG_GUEST_START_ADDRESS             0x40000000

#define CFG_HYP_START_ADDRESS				0x70000000


#endif  /* LAGER_CONFIG_H */
