#ifndef __MM_H__
#define __MM_H__

#define PGSIZE_4K 1
#if defined(PGSIZE_4K)

#define ENTRY_SHIFT 9
#define PAGE_SHIFT 12

#define L1_ENTRY    4
#define L2_ENTRY    512
#define L3_ENTRY    512

#define L3_SHIFT    PAGE_SHIFT
#define L2_SHIFT    (L3_SHIFT + ENTRY_SHIFT)
#define L1_SHIFT    (L2_SHIFT + ENTRY_SHIFT)

#define L1_INDEX_MASK 0xC0000000
#define L2_INDEX_MASK 0x3FE00000
#define L3_INDEX_MASK 0x001FF000

#define PAGE_MASK 0x00000FFF

#else
#endif // PAGE_2M

#endif /* __MM_H__*/
