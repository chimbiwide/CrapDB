#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../include/row.h"

void serialize_row(const Row *src, void *dest) {
    memcpy(dest + DELETED_OFFSET, &src->deleted, sizeof(uint8_t));
    memcpy(dest + ID_OFFSET, &src->id, sizeof(uint32_t));
    memcpy(dest + USRNAME_OFFSET, src->username, COLUMN_USRNAME_SIZE + 1);
    memcpy(dest + EMAIL_OFFSET, src->email, COLUMN_EMAIL_SIZE + 1);
}

void deserialize_row(const void *src, Row *dest) {
    memcpy(&dest->deleted, src + DELETED_OFFSET, sizeof(uint8_t));
    memcpy(&dest->id, src + ID_OFFSET, sizeof(uint32_t));
    memcpy(dest->username, src + USRNAME_OFFSET, COLUMN_USRNAME_SIZE + 1);
    memcpy(dest->email, src + EMAIL_OFFSET, COLUMN_EMAIL_SIZE + 1);
}

void print_row(const Row *row) {
    printf("ID: %d | USERNAME: %s | EMAIL: %s\n", row->id, row->username, row->email);
}
