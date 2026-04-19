// Command Parser

#ifndef PARSER_H
#define PARSER_H
#include "table.h"

//meta command status
typedef enum {
    META_SUCCESS,
    META_UNRECOGNIZED,
    META_EXIT
} MetaResult;

//SQL-Like statements
typedef enum {
    CMD_INSERT,
    CMD_SELECT,
    CMD_DELETE,
    CMD_UPDATE,
    CMD_COUNT,
    CMD_UNKNOWN
} CommandType;

//SQL-Like statement status
typedef enum {
    SQL_SUCCESS,
    SQL_UNRECOGNIZED
} ParseResult;

//struct for the command
typedef struct {
    CommandType type;
} Command;


//parser functions
MetaResult handle_meta(const char *input);
ParseResult parse_SQL(const char *input, Command *cmd);

#endif
