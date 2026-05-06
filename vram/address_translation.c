#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE   4096   /* 4 KB per page   */
#define NUM_PAGES   8      /* 8 virtual pages */
#define NUM_FRAMES  4      /* 4 frame di RAM  */

/*
 * Page table entry:
 *   frame_number = frame number fisik (-1 jika tidak ada di RAM)
 *   valid        = 1 jika page ada di RAM, 0 jika tidak
 */
typedef struct {
    int frame_number;
    int valid;
} PageTableEntry;

PageTableEntry page_table[NUM_PAGES];

/* init page table */
void init_page_table() {
    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i].frame_number = -1;
        page_table[i].valid        = 0;
    }
    /* simulasi ketika beberapa page sudah dimuat ke RAM */
    page_table[0].frame_number = 3;  page_table[0].valid = 1;
    page_table[2].frame_number = 1;  page_table[2].valid = 1;
    page_table[4].frame_number = 0;  page_table[4].valid = 1;
    page_table[6].frame_number = 2;  page_table[6].valid = 1;
}

/* address translation (virtual -> physical) */
int translate(unsigned int virtual_addr) {
    int page_num  = virtual_addr / PAGE_SIZE;
    int offset    = virtual_addr % PAGE_SIZE;

    printf("\n[Translation]\n");
    printf("  Virtual Address  : 0x%08X (%u)\n", virtual_addr, virtual_addr);
    printf("  Page Number      : %d\n", page_num);
    printf("  Offset           : %d (0x%X)\n", offset, offset);

    if (page_num >= NUM_PAGES) {
        printf("  ERROR: page number %d melebihi batas!\n", page_num);
        return -1;
    }

    if (!page_table[page_num].valid) {
        printf("  STATUS: PAGE FAULT - page %d tidak ada di RAM\n", page_num);
        return -1;
    }

    int frame  = page_table[page_num].frame_number;
    int phys   = frame * PAGE_SIZE + offset;

    printf("  Frame Number     : %d\n", frame);
    printf("  Physical Address : 0x%08X (%u)\n", phys, phys);
    printf("  STATUS: HIT\n");

    return phys;
}

void print_page_table() {
    printf("\n+-------+--------+-------+\n");
    printf("| Page  | Frame  | Valid |\n");
    printf("+-------+--------+-------+\n");
    for (int i = 0; i < NUM_PAGES; i++) {
        printf("|  %3d  |  %4d  |   %d   |\n",
               i,
               page_table[i].frame_number,
               page_table[i].valid);
    }
    printf("+-------+--------+-------+\n");
}

int main() {
    init_page_table();

    printf("=== Simulasi Address Translation ===\n");
    print_page_table();

    /* testing virtual address */
    unsigned int test_addresses[] = {
        0,        /* page 0, offset 0   — valid   */
        4096,     /* page 1, offset 0   — invalid */
        8450,     /* page 2, offset 258 — valid   */
        16384,    /* page 4, offset 0   — valid   */
        4097,     /* page 1             — invalid */
        36864     /* page 9             — out of range */
    };

    int n = sizeof(test_addresses) / sizeof(test_addresses[0]);
    for (int i = 0; i < n; i++) {
        translate(test_addresses[i]);
    }

    return 0;
}