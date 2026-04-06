#include <stdio.h>
#include <string.h>

#include "../include/parser.h"
#include "../include/color.h"

MetaResult handle_meta(const char *input) {
    if (strcmp(input, ".exit") == 0) {
        return META_EXIT;
    }
    else if (strcmp(input, ".help") == 0) {
        printf("%s--------HELP--------\n", GRN);
        printf("Meta Commands: .exit .help\n");
        printf("SQL Keywords: , SELECT, DELETE\n");
        printf("INSERT <id UNIQUE> <username: string> <bio: string>\n");
        printf("SELECT\n");
        printf("DELETE WHERE ID = <int>%s\n", RESET);
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

