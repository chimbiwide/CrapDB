#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/parser.h"

MetaResult handle_meta(const char *input) {
    if (strcmp(input, ".exit") == 0) {
        printf("~BYE~\n");
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(input, ".help") == 0) {
        printf("--------HELP--------\n");
        printf("Meta Commands: .exit .help\n");
        printf("SQL Keywords: , SELECT, DELETE\n");
        printf("INSERT <id UNIQUE> <username: string> <email: string>\n");
        printf("SELECT\n");
        printf("DELETE WHERE ID = <int>\n");
        return META_SUCCESS;
    }
    return META_UNRECOGNIZED;
}


ParseResult parse_SQL(const char *input, Command *cmd) {
    if (strncmp(input, "INSERT", 6) == 0) {
        cmd->type = CMD_INSERT;
        return SQL_SUCCESS;
    }
    else if (strncmp(input, "SELECT", 6) == 0) {
        cmd->type = CMD_SELECT;
        return SQL_SUCCESS;
    }
    else if (strncmp(input, "DELETE", 6) == 0) {
        cmd->type = CMD_DELETE;
        return SQL_SUCCESS;
    }
    return SQL_UNRECOGNIZED;
}

