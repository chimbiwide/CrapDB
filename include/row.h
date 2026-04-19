#ifndef ROW_H
#define ROW_H

#include <stdint.h>

//define fixed-size columns
#define COLUMN_USRNAME_SIZE 32
#define COLUMN_BIO_SIZE 255

//define offsets for serialization/deserialization
#define DELETED_OFFSET 0
#define ID_OFFSET (DELETED_OFFSET + sizeof(uint8_t))
#define USRNAME_OFFSET (ID_OFFSET + sizeof(uint32_t))
#define BIO_OFFSET (USRNAME_OFFSET + COLUMN_USRNAME_SIZE + 1)
#define ROW_SIZE (BIO_OFFSET + COLUMN_BIO_SIZE + 1)


//struct of a row
typedef struct {
    uint8_t deleted;
    uint32_t id;
    char username[COLUMN_USRNAME_SIZE + 1];
    char bio[COLUMN_BIO_SIZE + 1];
} Row;

//serialize a row struct into memory
void serialize_row(const Row *src, void *dest);
//deserialize a raw memory chunk into a Row struct
void deserialize_row(const void *src, Row *dest);
//pretty print a row information
void print_row(const Row *row);

#endif
