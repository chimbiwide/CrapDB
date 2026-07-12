#include <stdio.h>

#include "../include/error.h"
#include "../include/color.h"

void print_inc_usage(UsageSource source) {
    switch(source) {
        case SRC_INSERT: {
            fprintf(stderr, "%sUsage: INSERT <id: uint_32> <username: String> <bio: String>%s\n", RED, RESET);
            return;
        }
        case SRC_SELECT: {
            fprintf(stderr, "%sUsage: SELECT OR SELECT WHERE ID = <id: uint_32>%s\n", RED, RESET);
            return;
        }
        case SRC_DELETE: {
            fprintf(stderr, "%sUsage: DELETE WHERE ID = <id: uint_32>%s\n", RED, RESET);
            return;
        }
        case SRC_UPDATE: {
            fprintf(stderr,"%sUsage: UPDATE WHERE ID = <uint32> SET username = <string> bio = <string>%s\n", RED, RESET);
            return;
        }
        case SRC_COUNT: {
            fprintf(stderr, "%sUsage: COUNT%s\n", RED, RESET);
            return;
        }
        case SRC_DB: {
            fprintf(stderr, "%sUsage: ./crapdb <yourDbName.crap>%s\n", RED, RESET);
            return;
        }
        default: {
            fprintf(stderr, "%sError%s\n", RED, RESET);
            return;
        }
    }
}
