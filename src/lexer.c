#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_FileLine(const FileLine* fl) {
    // char txt[LGLZ_FILE_LINE_SZ];
    // strncpy(txt, fl->txt, LGLZ_FILE_LINE_SZ);
    printf("%s:%zu: %s\n", fl->file_path, fl->line_num, fl->txt);
}

size_t read_file_as_lines(const char* file_path, FileLine* file_as_lines) {
    FILE* fp = fopen(file_path, "r");
    if (!fp) {
        printf("[ERRO] File [%s] does not exist\n", file_path);
        return 0;
    }

    size_t num_lines = 0;
    char* buf; size_t len;
    while (getline(&buf, &len, fp) != -1) {
        printf("%s\n", buf);
    }

    fclose(fp);

    return num_lines;
}