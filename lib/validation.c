#include "validation.h"
#include <stdio.h>

bool is_circuit_valid(void *value) {
    const ushort *temp = (ushort *)value;
    return *temp > 0 && *temp <= 4;
}

bool is_positive(void *value) {
    const double *temp = (double *)value;
    return *temp > 0;
}

void get_input(const DataType type, void *variable, const char *print_msg, bool (*condition)(void*), const char *error_msg) {
    const char *format = NULL;
    switch (type) {
        case TYPE_USHORT: {
            format = "%hu";
        } break;
        case TYPE_DOUBLE: {
            format = "%lf";
        } break;
        default: {
            printf("Error: unsupported data type used in get_input().\n");
            return;
        }
    }

    do {
        printf(print_msg);
        if (scanf(format, variable) != 1) {
            printf("%s", "Error: wrong input.");
        } else if (!condition(variable)) {
            printf("%s", error_msg);
        }
        while (getchar() != '\n');
    } while (!condition(variable));
}