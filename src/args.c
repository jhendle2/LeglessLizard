#include "args.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Argument new_arg(const char c, const char* kw, const size_t nargs, const enum ArgumentAction action) {
    Argument arg = {
        .dirty = false,
        .c = c,
        .nargs = nargs,
        .action = action,
        .args.len = 0,
    };
    strncpy(arg.kw, kw, LGLZ_ARG_SZ);
    return arg;
}

size_t parse_args(const int argc, char** argv, Argument* args) {
    args = (Argument*)malloc(sizeof(Argument)*argc); /* Will guarantee we always have enough space but bulky */
    size_t len = 0;

    Argument temp = {.c = 0};
    for (size_t i = 1; i<argc; i++) {
        if (argv[i][0] == '-') {
            if (temp.c != 0) args[len++] = temp; /* Append last */
            if (argv[i][1] != '-') {
                temp.c = argv[i][1];
            } else {
                strncpy(temp.kw, argv[i]+2, LGLZ_ARG_SZ);
            }
        }
        else {
            strncpy(temp.args.args[temp.args.len++], argv[i], LGLZ_ARG_SZ);
        }
    }

    return len;
}

bool register_arg(ArgumentMap arg_map, const Argument arg) {
    size_t index = (int)(arg.c);
    printf("index<%c>=%zu\n", arg.c, index);
    if (arg_map[(int)(arg.c)].dirty) return false;
    arg_map[(int)(arg.c)]       = arg;
    arg_map[(int)(arg.c)].dirty = true;
    return true;
}