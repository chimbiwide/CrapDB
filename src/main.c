#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../include/table.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/color.h"

int main(int argc, char *argv[]) {
    //ignore Ctrl+C
    signal(SIGINT, SIG_IGN);
    //if didnt provide a .crap file, exit
    if (argc != 2) {
        printf("%sUsage: ./crapdb <yourDbName.crap>%s\n", RED, RESET);
        exit(2);
    }
    size_t len = strlen(argv[1]);
    if (len < 5 || strcmp(argv[1] + len - 5, ".crap") != 0){
        printf("%sError: file must have .crap extenstion%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    Table* table = table_open(argv[1]);
    while (1) {
        Command cmd;
        char buffer[1024];

        printf("crapdb> ");
        fflush(stdout);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            //EOF Exit
            printf("%s~~~BYE~~~%s\n", YEL, RESET);
            break;
        }

        //replaces \n with \0
        buffer[strcspn(buffer, "\n")] = '\0';
        //if line is empty continue
        if (buffer[0] == '\0') {continue;}

        //if the input is a meta command
        if (buffer[0] == '.') {
            MetaResult result = handle_meta(buffer);
            if (result == META_UNRECOGNIZED) {
                printf("%sUnrecognized Meta Command: '%s', Try Again%s\n", RED, buffer, RESET);
            }
            else if (result == META_EXIT) {
                printf("---------BYE---------\n");
                break;
            }
            continue;
        }
        
        if (parse_SQL(buffer, &cmd) == SQL_UNRECOGNIZED) {
            printf("%sUnrecognized SQL Command: '%s', Try Again%s\n", RED, buffer, RESET);
            continue;
        }
        execute_command(&cmd, table, buffer);
    }
    table_close(table);
    return 0;
}
