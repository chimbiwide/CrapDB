#ifndef ROW_H
#define ROW_H

#include <stdint.h>

#define COLUMN_USRNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

#define DELETED_OFFSET 0
#define ID_OFFSET (DELETED_OFFSET + sizeof(uint8_t))
#define USRNAME_OFFSET (ID_OFFSET + sizeof(uint32_t))
#define EMAIL_OFFSET (USRNAME_OFFSET + COLUMN_USRNAME_SIZE + 1)
#define ROW_SIZE (EMAIL_OFFSET + COLUMN_EMAIL_SIZE + 1)


typedef struct {
    uint8_t deleted;
    uint32_t id;
    char username[COLUMN_USRNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

void serialize_row(const Row *src, void *dest);
void deserialize_row(const void *src, Row *dest);
void print_row(const Row *row);

#endif
