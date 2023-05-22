#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "lexer.h"

int main(int argc, char** argv) {

    if (argc < 2) return FAILURE;
    const char* file_path = argv[1];
    printf("[%s]\n", file_path);

    FileLine* file_as_lines = NULL;
    const size_t file_as_lines_sz = read_file_as_lines(file_path, &file_as_lines);

    for (size_t i = 0; i<file_as_lines_sz; i++) {
        // print_file_line(file_as_lines+i);
        Token* line_as_tokens = NULL;
        const size_t num_tokens = tokenize_line(file_as_lines[i], &line_as_tokens);
        for (size_t j = 0; j<num_tokens; j++)
            printf("[%s] ", line_as_tokens[j].txt);
            // print_token(line_as_tokens+j);
        // free(line_as_tokens);
        printf("\n");
    }

    if (file_as_lines) free(file_as_lines);
    
    return SUCCESS;
}