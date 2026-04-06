#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/table.h"

Table* table_open(char *filename) {
    FILE *file = fopen(filename, "r+b");
    //if file doesnt exist
    if (file == NULL) {
        file = fopen(filename, "w+b");
    }
    Table *table = malloc(sizeof(Table));
    if (table == NULL) {
        fprintf(stderr, "Memory Allocation Failed");
        exit(EXIT_FAILURE);
    }
    if (fread(&table->num_rows, sizeof(uint32_t), 1, file) != 1){
        table->num_rows = 0;
    }
    table->filename = filename;
    table->file = file;
    for (int i = 0; i < TABLE_MAX_PAGES; i++) {
        table->pages[i] = NULL;
    }
    return table;
}

void table_close(Table *table) {
    fseek(table->file, 0, SEEK_SET);
    fwrite(&table->num_rows, sizeof(uint32_t), 1, table->file);
    for (int i = 0; i < TABLE_MAX_PAGES; i++) {
        if (table->pages[i] != NULL) {
            fseek(table->file, ROWS_OFFSET + (i * PAGE_SIZE), SEEK_SET);
            fwrite(table->pages[i], PAGE_SIZE, 1, table->file);
            free(table->pages[i]);
        }
    }
    fclose(table->file);
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
        //check if the db file has data
        if (fseek(table->file, ROWS_OFFSET + (page_num * PAGE_SIZE), SEEK_SET) == 0) {
            fread(page, PAGE_SIZE, 1, table->file);
        }
        table->pages[page_num] = page;
    }
    page = table->pages[page_num];
    uint32_t overflow = row_num % ROWS_PER_PAGE;
    return page + (overflow * ROW_SIZE);
}
