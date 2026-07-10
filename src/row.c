#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../include/row.h"
#include "../include/color.h"

//memcpy is used because of the padding bytes that C might add to structs
void serialize_row(const Row *src, void *dest) {
    memcpy(dest + DELETED_OFFSET, &src->deleted, sizeof(uint8_t));
    memcpy(dest + ID_OFFSET, &src->id, sizeof(uint32_t));
    memcpy(dest + USRNAME_OFFSET, src->username, COLUMN_USRNAME_SIZE + 1);
    memcpy(dest + BIO_OFFSET, src->bio, COLUMN_BIO_SIZE + 1);
}

void deserialize_row(const void *src, Row *dest) {
    memcpy(&dest->deleted, src + DELETED_OFFSET, sizeof(uint8_t));
    memcpy(&dest->id, src + ID_OFFSET, sizeof(uint32_t));
    memcpy(dest->username, src + USRNAME_OFFSET, COLUMN_USRNAME_SIZE + 1);
    memcpy(dest->bio, src + BIO_OFFSET, COLUMN_BIO_SIZE + 1);
}

void print_row(const Row *row) {
    printf("%sID: %d | USERNAME: %s | BIO: %s%s\n", YEL, row->id, row->username, row->bio, RESET);
}
