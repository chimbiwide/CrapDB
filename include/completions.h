#ifndef COMPLETION_H
#define COMPLETION_H

#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

char *commands[] = {
    "INSERT", "SELECT", "SELECT WHERE ID = ",
    "DELETE WHERE ID = ", ".exit", ".help", NULL
};

char *command_generator(const char *text, int state) {
    static int list_index;
    if (!state) list_index = 0;
    while(commands[list_index]) {
        char *cmd = commands[list_index++];
        if (strncmp(cmd, text, strlen(text)) == 0) {
            return strdup(cmd);
        }
    }
}

#endif
