#ifndef LGLZ_LEXER_H
#define LGLZ_LEXER_H

#include <stddef.h>

#define LGLZ_PATH_SZ 64
#define LGLZ_FILE_LINE_SZ 256

typedef struct {
    size_t line_num;
    char file_path[LGLZ_PATH_SZ];
    char txt[LGLZ_FILE_LINE_SZ];
} FileLine;

void print_file_line(const FileLine* fl);

size_t read_file_as_lines(const char* file_path, FileLine** file_as_lines);

#define LGLZ_TOKEN_SZ 16
#define LGLZ_TOKENS_IN_LINE LGLZ_FILE_LINE_SZ/LGLZ_TOKEN_SZ

typedef struct {
    FileLine parent;
    size_t offset;
    char txt[LGLZ_TOKEN_SZ];
} Token;

size_t tokenize_line(const FileLine file_line, Token** tokens);
void print_token(const Token* tok);

#endif /* LGLZ_LEXER_H */