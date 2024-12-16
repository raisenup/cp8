#pragma once
#include <stdbool.h>

typedef unsigned short ushort;

typedef enum {
    TYPE_USHORT,
    TYPE_DOUBLE,
} DataType;

bool is_circuit_valid(void *value);

bool is_positive(void *value);

void get_input(const DataType type, void *variable, const char *print_msg, bool (*condition)(void*), const char *error_msg);
