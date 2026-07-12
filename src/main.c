#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

#include "../include/table.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/color.h"
#include "../include/error.h"

int main(int argc, char *argv[]) {
    //ignore Ctrl+C
    signal(SIGINT, SIG_IGN);
    //if didnt provide a .crap file, exit
    if (argc != 2) {
        print_inc_usage(SRC_DB);
        exit(2);
    }
    size_t len = strlen(argv[1]);
    if (len < 5 || strcmp(argv[1] + len - 5, ".crap") != 0){
        printf("%sError: file must have .crap extenstion%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }

    Table* table = table_open(argv[1]);
    if (table == NULL) {
        fprintf(stderr, "%sError: could not open database '%s': %s%s\n",
                RED, argv[1], strerror(errno), RESET);
        exit(EXIT_FAILURE);
    }
    while (1) {
        Command cmd;
        char buffer[1024];

        printf("crapdb> ");
        fflush(stdout);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            //EOF Exit
            printf("%s---BYE---%s\n", YEL, RESET);
            break;
        }

        // convert to string
        buffer[strcspn(buffer, "\n")] = '\0';
        //if no input
        if (buffer[0] == '\0') continue;

        //if the input is a meta command
        if (buffer[0] == '.') {
            MetaResult result = handle_meta(buffer);

            if (result == META_UNRECOGNIZED) continue;
            else if (result == META_SUCCESS) continue;
            else if (result == META_EXIT) break;
        }
        if (parse_SQL(buffer, &cmd) == SQL_UNRECOGNIZED) {
            continue;
        }
        execute_command(&cmd, table, buffer);
    }
    if (table_close(table) != 0) {
        fprintf(stderr, "%sError: cannot write '%s' to file%s\n",
                RED, argv[1], RESET);
        return EXIT_FAILURE;
    }
    table = NULL;
    return 0;
}
