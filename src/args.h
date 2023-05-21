#ifndef LGLZ_ARGS_H
#define LGLZ_ARGS_H

#include <stdbool.h>
#include <stddef.h>

#define LGLZ_ARG_SZ 32
#define LGLZ_MAX_ARGS 16
#define LGLZ_ARG_MAP_SZ 256

enum ArgumentAction {
    AA_NONE,
    AA_COPY_VALUE,
    AA_STORE_TRUE,
    AA_STORE_FALSE
};

typedef struct {
    bool dirty;
    char c;
    char kw[LGLZ_ARG_SZ];
    size_t nargs;
    enum ArgumentAction action;

    struct {
        size_t len;
        char args[LGLZ_MAX_ARGS][LGLZ_ARG_SZ];
    } args;
} Argument;

typedef Argument ArgumentMap[LGLZ_ARG_MAP_SZ];

Argument new_arg(const char c, const char* kw, const size_t nargs, const enum ArgumentAction action);
size_t parse_args(const int argc, char** argv, Argument* args);
bool register_arg(ArgumentMap arg_map, const Argument arg);

#endif /* LGLZ_ARGS_H */