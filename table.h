#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include "row.h"

//define table structure 
//fixed size for now
#define PAGE_SIZE 4096
#define TABLE_MAX_PAGES 100
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS (TABLE_MAX_PAGES * ROWS_PER_PAGE)

typedef struct {
    uint32_t num_rows;
    void *pages[TABLE_MAX_PAGES];  //starts as NULL
} Table;

void table_open()

#endif
