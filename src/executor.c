#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "../include/parser.h"
#include "../include/color.h"

void execute_command(Command *cmd, Table *table, const char *input) {
    switch(cmd->type){
        case CMD_INSERT: {
            uint32_t id;
            char username[COLUMN_USRNAME_SIZE + 1];
            char bio[COLUMN_BIO_SIZE + 1];
            if (sscanf(input, "INSERT %d %33s %255s;", &id, username, bio) == 3){
                Row row;
                row.id = id;
                row.deleted = 0;
                uint8_t duplicate = 0;

                for (uint32_t i = 0; i < table->num_rows; i++) {
                    Row current;
                    deserialize_row(row_slot(table, i), &current);
                    if (row.id == current.id && !current.deleted) {
                        duplicate = 1;
                        break;
                    }
                }
                if (duplicate) printf("%sDuplicate Values%s\n", RED, RESET);
                else {
                    strncpy(row.username, username, COLUMN_USRNAME_SIZE+1);
                    strncpy(row.bio, bio, COLUMN_BIO_SIZE+1);
                    serialize_row(&row, row_slot(table, table->num_rows));
                    table->num_rows++;
                    printf("%sINSERTED%s\n", GRN, RESET);
                }
            }
            else printf("%sUsage: INSERT <id: uint_32> <username: String> <bio: String>%s\n", RED, RESET);
            break;
        }
        case CMD_SELECT: {
            uint8_t valid = 0;
            uint32_t id;
            if (sscanf(input, "SELECT WHERE ID = %d", &id) == 1) {
                valid = 1;
                for (uint32_t i = 0; i < table->num_rows; i++) {
                    Row output;
                    deserialize_row(row_slot(table, i), &output);
                    if (output.deleted || output.id != id) continue;
                    print_row(&output);
                }
            }
            else {
                valid = 1;
                for (uint32_t i = 0; i < table->num_rows; i++) {
                    Row output;
                    deserialize_row(row_slot(table, i), &output);
                    if (output.deleted) continue;
                    print_row(&output);
                }
            }
            if (valid) break;
            else printf("%sUsage: SELECT OR SELECT WHERE ID = <id: uint_32>%s\n", RED, RESET);
            break;
        }
        case CMD_DELETE: {
            uint8_t found = 0;
            uint32_t id;
            if (sscanf(input, "DELETE WHERE ID = %d;", &id) == 1) {
                for (uint32_t i = 0; i < table->num_rows; i++) {
                    Row current;
                    deserialize_row(row_slot(table, i), &current);
                    if (id == current.id) {
                        current.deleted = 1;
                        found = 1;
                        serialize_row(&current, row_slot(table, i));
                    }
                }
                if (found) printf("%sDeleted%s\n", GRN, RESET);
                else printf("Row not found\n");
            }
            else printf("%sRow with ID: '%d' not found%s\n", RED,id, RESET);
            break;
        }
        default:
            break;
    }
}
