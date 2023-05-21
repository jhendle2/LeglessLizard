#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "lexer.h"

int main(int argc, char** argv) {

    if (argc < 2) return FAILURE;
    const char* file_path = argv[1];
    printf("[%s]\n", file_path);

    FileLine* file_as_lines = NULL;
    const size_t file_as_lines_sz = read_file_as_lines(file_path, file_as_lines);
    if (file_as_lines) free(file_as_lines);

    return SUCCESS;
}