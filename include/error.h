// Printing Error messages
#ifndef ERROR_H
#define ERROR_H

// message source
typedef enum {
    SRC_INSERT,
    SRC_SELECT,
    SRC_DELETE,
    SRC_UPDATE,
    SRC_COUNT,
    SRC_DB,
} UsageSource;

//message type
typedef enum {
    TYPE_USAGE,
    TYPE_ERROR,
    TYPE_SUCCESS
} MessageType;

// print incorrect usage
void print_inc_usage(UsageSource source);

#endif
