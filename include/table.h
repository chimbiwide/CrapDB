#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdint.h>
#include "row.h"

//define table structure 
//fixed size for now
#define ROWS_OFFSET sizeof(uint32_t)
#define PAGE_SIZE 4096
#define TABLE_MAX_PAGES 100
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS (TABLE_MAX_PAGES * ROWS_PER_PAGE)

//the stuct for the table
typedef struct {
    FILE *file;
    char *filename;
    uint32_t num_rows;
    void *pages[TABLE_MAX_PAGES];  //starts as NULL
} Table;

// enum for errors
typedef enum {
    DB_OK,
    DB_ERR_IO,
    DB_ERR_NOMEM,
    DB_ERR_CORRUPT
} DBStatus;

//allocate memory for a table
//either reads data from the .crap file or creates a new file
Table* table_open(char *filename);
//writes all information to the file before freeing
int table_close(Table* table);
//return a pointer to where a row shoudl be 
void* row_slot(Table* table, uint32_t row_num);

#endif
