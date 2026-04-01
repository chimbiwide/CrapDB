#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "table.h"

Table* table_open() {
    Table *table = malloc(sizeof(Table));
    if (table == NULL) {
        fprintf(stderr, "Memory Allocation Failed");
        exit(EXIT_FAILURE);
    }
    table->num_rows = 0;
    for (int i = 0; i < TABLE_MAX_PAGES; i++) {
        table->pages[i] = NULL;
    }
    return table;
}

void table_close(Table *table) {
    for (int i = 0; i < TABLE_MAX_PAGES; i++) {
        if (table->pages[i] != NULL) {
            free(table->pages[i]);
        }
    }
    free(table);
}

void* row_slot(Table* table, uint32_t row_num) {
    //which page does it belong to
    uint32_t page_num = (int)row_num / ROWS_PER_PAGE;
    void* page;
    if (table->pages[page_num] == NULL) {
        page = malloc(PAGE_SIZE);
        if (page == NULL) {
            fprintf(stderr, "Memory Allocation Failed");
            exit(EXIT_FAILURE);
        }
        table->pages[page_num] = page;
    }
    page = table->pages[page_num];
}
