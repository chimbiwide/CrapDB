//executor for SQL commands

#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "table.h"
#include "parser.h"

void execute_command(Command *cmd, Table *table, const char *input);

#endif
