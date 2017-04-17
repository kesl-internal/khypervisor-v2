#include <core/vm/vmem.h>
#include <config.h>
#include <arch/armv7.h>
#include <size.h>
#include "../../arch/arm/paging.h"
#include <vm_map.h>
#include <vm_config.h>
#include <stdio.h>

extern uint32_t __VM_PGTABLE;

#define PGTABLE_SIZE    0x805000

#define VTTBR_VMID_MASK                                 0x00FF000000000000ULL
#define VTTBR_VMID_SHIFT                                48
#define VTTBR_BADDR_MASK                                0x000000FFFFFFFFFFULL

extern struct vm_config vm_conf[];

void vmem_create(struct vmem *vmem, vmid_t vmid)
{
    vmem->base = (uint32_t) &__VM_PGTABLE + (PGTABLE_SIZE * vmid);
    paging_create(vmem->base);

    vmem->vttbr = ((uint64_t) vmid << VTTBR_VMID_SHIFT) & VTTBR_VMID_MASK;
    vmem->vttbr &= ~(VTTBR_BADDR_MASK);
    vmem->vttbr |= (uint32_t) vmem->base & VTTBR_BADDR_MASK;

    vmem->mmap = vm_mmap[vmid];
}

hvmm_status_t vmem_init(struct vmem *vmem, vmid_t vmid)
{
    int j = 0;

    while (vmem->mmap[j].label != 0) {
        paging_add_ipa_mapping(vmem->base, vmem->mmap[j].ipa, vmem->mmap[j].pa, vmem->mmap[j].attr, vmem->mmap[j].af,
                               vmem->mmap[j].size);
        j++;
    }

    paging_add_ipa_mapping(vmem->base, CONFIG_VA_START, vm_conf[vmid].pa_start, MEMATTR_NORMAL_WB_CACHEABLE, 1,
                           vm_conf[vmid].va_offsets);

    vmem->actlr = read_cp32(ACTLR);

    if (vm_conf[vmid].nr_vcpus > 1) {
        vmem->actlr |= (1 << 6);
    }

    vmem->vtcr = (VTCR_SL0_FIRST_LEVEL << VTCR_SL0_BIT);
    vmem->vtcr |= (WRITEBACK_CACHEABLE << VTCR_ORGN0_BIT);
    vmem->vtcr |= (WRITEBACK_CACHEABLE << VTCR_IRGN0_BIT);
    write_cp32(vmem->vtcr, VTCR);

    return HVMM_STATUS_SUCCESS;
}

hvmm_status_t vmem_save(void)
{
    uint32_t hcr = 0;
    hcr = read_cp32(HCR);
    write_cp32((hcr & ~HCR_BIT(VM)), HCR);

    return HVMM_STATUS_SUCCESS;
}

hvmm_status_t vmem_restore(struct vmem *vmem)
{
    uint32_t hcr = 0;

    write_cp32(vmem->vtcr, VTCR);
    write_cp32(vmem->actlr, ACTLR);
    write_cp64(vmem->vttbr, VTTBR);

    hcr = read_cp32(HCR);
    write_cp32((hcr | HCR_BIT(VM)), HCR);

    return HVMM_STATUS_SUCCESS;
}

#include <string.h>
#include <vm_config.h>
void vmem_copy(struct vmem *from, struct vmem *to)
{
//    to->mmap = from->mmap;
//    to->base = from->base;
//    to->vtcr = from->vtcr;
//    to->actlr = from->actlr;
//    to->vttbr = from->vttbr;

    to->vtcr = from->vtcr;
    to->actlr = from->actlr;

    // copy all of the physical memory
    printf("%s[%d] offset[%x]\n", __func__, __LINE__, vm_conf[1].va_offsets);
    uint32_t offset = 0;
    uint32_t from_mem = vm_conf[0].pa_start;
    uint32_t to_mem   = vm_conf[1].pa_start;

    for (offset = 0; offset < vm_conf[1].va_offsets; offset+=4) {
//        printf("before offset[%x] %s[%d]\n", offset, __func__, __LINE__);
        writel(readl(from_mem + offset), (to_mem + offset));
//        printf("after offset[%x] %s[%d]\n", offset, __func__, __LINE__);
    }
    printf("%s[%d]\n", __func__, __LINE__);
}

