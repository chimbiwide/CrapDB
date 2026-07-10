#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "../include/table.h"

Table* table_open(char *filename) {
    FILE *file = fopen(filename, "r+b");
    //if file doesnt exist
    if (file == NULL) file = fopen(filename, "w+b");
    //fopen still failed for some reason
    if (file == NULL) return NULL;

    Table *table = malloc(sizeof(Table));
    if (table == NULL) goto close_file;

    if (fread(&table->num_rows, sizeof(uint32_t), 1, file) != 1){
        table->num_rows = 0;
    }
    table->filename = filename;
    table->file = file;
    for (int i = 0; i < TABLE_MAX_PAGES; i++) {
        table->pages[i] = NULL;
    }
    return table;

close_file: ;
    int error = errno;
    free(table);
    fclose(file);
    errno = error;
    return NULL;
}

int table_close(Table *table) {
    int status = 0; // 0 = success, -1 = write failed
    //reset the file pointer
    fseek(table->file, 0, SEEK_SET);
    //writes the num_rows first
    if (fwrite(&table->num_rows, sizeof(uint32_t), 1, table->file) != 1) 
        status = -1;
    //write page -> free that page
    for (int i = 0; i < TABLE_MAX_PAGES; i++) {
        if (table->pages[i] != NULL) {
            fseek(table->file, ROWS_OFFSET + (i * PAGE_SIZE), SEEK_SET);
            if (fwrite(table->pages[i], PAGE_SIZE, 1, table->file) != 1)
                status = -1;
            free(table->pages[i]);
        }
    }
    if (fclose(table->file) != 0)
        status = -1;
    free(table);
    return status;
}

void* row_slot(Table* table, uint32_t row_num) {
    //which page does it belong to
    uint32_t page_num = (int)row_num / ROWS_PER_PAGE;
    void* page;
    if (table->pages[page_num] == NULL) {
        page = malloc(PAGE_SIZE);
        if (page == NULL) return NULL;
        //check if the db file has data
        if (fseek(table->file, ROWS_OFFSET + (page_num * PAGE_SIZE), SEEK_SET) == 0) {
            fread(page, PAGE_SIZE, 1, table->file);
        }
        table->pages[page_num] = page;
    }
    page = table->pages[page_num];
    uint16_t overflow = row_num % ROWS_PER_PAGE;
    return page + (overflow * ROW_SIZE);
}
