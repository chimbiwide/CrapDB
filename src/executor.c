#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#include "../include/parser.h"
#include "../include/color.h"
#include "../include/error.h"

void execute_command(Command *cmd, Table *table, const char *input) {
    switch(cmd->type){
        case CMD_INSERT: {
            uint32_t id;
            char username[COLUMN_USRNAME_SIZE + 1];
            char bio[COLUMN_BIO_SIZE + 1];
            if (sscanf(input, "INSERT %d %32s %255s;", &id, username, bio) == 3){
                Row row;
                row.id = id;
                row.deleted = 0;
                uint8_t duplicate = 0;

                // check for duplicates
                for (uint32_t i = 0; i < table->num_rows; i++) {
                    Row current;
                    void* target_row = row_slot(table, i);
                    // check if overflow
                    if (target_row == NULL) {
                        printf("%sMaximum row number exceeded, open a new db%s\n", RED, RESET);
                        break;
                    }
                    deserialize_row(target_row, &current);
                    if (row.id == current.id && !current.deleted) {
                        duplicate = 1;
                        break;
                    }
                }
                if (duplicate) printf("%sDuplicate Values%s\n", RED, RESET);
                //insert
                else {
                    void* target_row = row_slot(table, table->num_rows);
                    if (target_row == NULL) {
                        printf("%sMaximum row number exceeded, open a new db%s\n", RED, RESET);
                        break;
                    }
                    strncpy(row.username, username, COLUMN_USRNAME_SIZE+1);
                    strncpy(row.bio, bio, COLUMN_BIO_SIZE+1);
                    serialize_row(&row, target_row);
                    table->num_rows++;
                    printf("%sINSERTED%s\n", GRN, RESET);
                }
            }
            else print_inc_usage(SRC_INSERT);
            break;
        }
        case CMD_SELECT: {
            uint8_t valid = 0;
            uint32_t id;
            if (sscanf(input, "SELECT WHERE ID = %d", &id) == 1) {
                valid = 1;
                for (uint32_t i = 0; i < table->num_rows; i++) {
                    Row output;
                    void* target_row = row_slot(table, i);
                    if (target_row == NULL) {

                    }
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
            else print_inc_usage(SRC_SELECT);
            break;
        }
        case CMD_DELETE: {
            uint8_t found = 0;
            uint32_t id = 0;
            if (sscanf(input, "DELETE WHERE ID = %d", &id) == 1) {
                for (uint32_t i = 0; i < table->num_rows; i++) {
                    Row current;
                    Row *target = row_slot(table, i);
                    if (target == NULL) {
                        fprintf(stderr, "%sError: unable to delete row %d: '%s'%s\n",
                                RED, id, strerror(errno), RESET);
                        break;
                    }
                    deserialize_row(target, &current);
                    if (id == current.id) {
                        current.deleted = 1;
                        found = 1;
                        serialize_row(&current, target);
                    }
                }
                if (found) printf("%sDeleted%s\n", GRN, RESET);
                else printf("Row not found\n");
            }
            else print_inc_usage(SRC_DELETE);
            break;
        }
        case CMD_UPDATE: {
            uint32_t target_id;
            char new_usrname[COLUMN_USRNAME_SIZE + 1];
            char new_bio[COLUMN_BIO_SIZE + 1];
            if (sscanf(input, "UPDATE WHERE ID = %u SET username = %32s bio = %255s", &target_id, new_usrname, new_bio) == 3) {
                uint8_t found = 0;
                for (uint32_t i = 0; i < table->num_rows; i++) {
                    Row current;
                    deserialize_row(row_slot(table, i), &current);
                    if (current.id == target_id && !current.deleted) {
                        strncpy(current.username, new_usrname, COLUMN_USRNAME_SIZE+1);
                        strncpy(current.bio, new_bio, COLUMN_BIO_SIZE+1);
                        serialize_row(&current, row_slot(table, i));
                        printf("%sUPDATED%s\n", GRN, RESET);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("%sRow with ID = %u not found%s\n", RED, target_id, RESET);
            }
            else print_inc_usage(SRC_UPDATE);
            break;
        }
        case CMD_COUNT: {
            uint32_t count = 0;
            if (strcmp(input, "COUNT") == 0) {
                for (uint32_t i = 0; i < table->num_rows; i++) {
                    Row current;
                    deserialize_row(row_slot(table, i), &current);
                    if (!current.deleted) {
                        count++;
                    }
                }
                printf("%sTotal Rows: %u %s\n", GRN, count, RESET);
                break;
            }
            else print_inc_usage(SRC_COUNT);
            break;
        }
        default:
            break;
    } 
}
