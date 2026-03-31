#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//meta commands
typedef enum {
    META_SUCCESS,
    META_UNRECOGNIZED
} MetaResult;

//SQL-Like statements
typedef enum {
    CMD_INSERT,
    CMD_SELECT,
    CMD_DELETE,
    CMD_UNKNOWN
} CommandType;

typedef enum {
    SQL_SUCCESS,
    SQL_UNRECOGNIZED
} ParseResult;

//struct for the command
typedef struct {
    CommandType type;
} Command;

//define function outline
//
MetaResult handle_meta(const char *input);
ParseResult parse_SQL(const char *input, Command *cmd);
void execute_command(Command *cmd);

int main() {
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
        execute_command(&cmd);
    }
    return 0;
}


MetaResult handle_meta(const char *input) {
    if (strcmp(input, ".exit") == 0) {
        printf("~BYE~\n");
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(input, ".help") == 0) {
        printf("Meta Commands: .exit .help \n SQL Keywords: INSERT, SELECT, DELETE\n");
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

void execute_command(Command *cmd) {
    switch(cmd->type){
        case CMD_INSERT:
            printf("INSERT not yet implmented. \n");
            break;
        case CMD_SELECT:
            printf("SELECT not yet implemented. \n");
            break;
        case CMD_DELETE:
            printf("DELETE not yet implenmented. \n");
            break;
        default:
            break;
    }
}
