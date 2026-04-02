#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/table.h"
#include "../include/parser.h"
#include "../include/executor.h"

int main() {
    Table* table = table_open();
    while (1) {
        char buffer[1024];
        Command cmd;

        printf("crapdb> ");
        fflush(stdout);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            //EOF exit
            printf("~BYE~\n");
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        if (buffer[0] == '\0') {continue;}

        if (buffer[0] == '.') {
            if (handle_meta(buffer) == META_UNRECOGNIZED) {
                printf("Unrecognized Meta Command: '%s', Try Again\n", buffer);
            }
            continue;
        }
        
        if (parse_SQL(buffer, &cmd) == SQL_UNRECOGNIZED) {
            printf("Unrecognized SQL Command: '%s', Try Again\n", buffer);
            continue;
        }
        execute_command(&cmd, table, buffer);
    }
    table_close(table);
    return 0;
}
