#ifndef LGLZ_LEXER_H
#define LGLZ_LEXER_H

#include <stddef.h>

#define LGLZ_PATH_SZ 64
#define LGLZ_FILE_LINE_SZ 128

typedef struct {
    size_t line_num;
    char file_path[LGLZ_PATH_SZ];
    char txt[LGLZ_FILE_LINE_SZ];
} FileLine;

void print_FileLine(const FileLine* fl);

size_t read_file_as_lines(const char* file_path, FileLine* file_as_lines);

#endif /* LGLZ_LEXER_H */