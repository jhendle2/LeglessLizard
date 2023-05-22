#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ops_delims.h"

void print_file_line(const FileLine* fl) {
    char txt[LGLZ_FILE_LINE_SZ];
    strncpy(txt, fl->txt, LGLZ_FILE_LINE_SZ);
    size_t len = strlen(txt);
    txt[len-1] = 0;
    printf("%s:%zu: %s\n", fl->file_path, fl->line_num+1, txt);
}

size_t read_file_as_lines(const char* file_path, FileLine** file_as_lines) {
    FILE* fp = fopen(file_path, "r");
    if (!fp) {
        printf("[ERRO] File [%s] does not exist\n", file_path);
        return 0;
    }

    FileLine fls[1024];
    size_t line_num = 0;
    size_t len = 0;
    char* buffer = (char*)malloc(sizeof(char)*LGLZ_FILE_LINE_SZ);
    char* buf = buffer;
    while (getline(&buf, &len, fp) != -1) {
        FileLine fl = { .line_num = line_num };
        strncpy(fl.file_path, file_path, LGLZ_PATH_SZ);
        strncpy(fl.txt, buf, LGLZ_FILE_LINE_SZ);
        fls[line_num++] = fl;
    }

    fclose(fp);
    if(buffer) free(buffer);

    (*file_as_lines) = (FileLine*)malloc(sizeof(FileLine)*line_num);
    memcpy(*file_as_lines, fls, sizeof(FileLine)*line_num);

    return line_num;
}

size_t tokenize_line(const FileLine file_line, Token** tokens) {
    Token tks[LGLZ_TOKENS_IN_LINE];
    size_t num_tokens = 0;

    #define LAMBDA_add_to_token(TOKEN, INDEX, CHAR) \
        {\
            TOKEN.txt[INDEX++] = CHAR;\
        }

    #define LAMBDA_append_token(TOKEN, INDEX, OFFSET) \
        {\
            if (INDEX > 0) {\
                TOKEN.offset = OFFSET-strlen(TOKEN.txt)+1;\
                TOKEN.txt[INDEX]  = 0;\
                tks[num_tokens++] = TOKEN;\
                INDEX = 0;\
            }\
        }

    Token temp = { .offset = 0, .parent = file_line };
    size_t temp_index = 0;
    // size_t indent = 0; bool indent_switch = true;
    const size_t len = strlen(file_line.txt);
    bool in_quote_single = false/*, in_quote_double = false*/;

    for (size_t i = 0; i<len; i++) {
        const char c = file_line.txt[i];
        // if (indent_switch) {
        //     if (c == ' ') indent++;
        //     else indent_switch = false;
        // }

        if (c == LGLZ_DELIM_QUOTE_SINGLE) {
            if (in_quote_single) {
                LAMBDA_add_to_token(temp, temp_index, c);
                LAMBDA_append_token(temp, temp_index, i);
                in_quote_single = false;
                continue;
            } else {
                LAMBDA_append_token(temp, temp_index, i);
                LAMBDA_add_to_token(temp, temp_index, c);
                in_quote_single = true;
                continue;
            }
        }
        if (in_quote_single) goto add_char;

        if (c == ' ') {
            LAMBDA_append_token(temp, temp_index, i);
            continue;
        }
        else if (c == LGLZ_DELIM_COMMENT) {
            LAMBDA_append_token(temp, temp_index, i);
            break;
        }
        else if (isDelim(c)) {
            LAMBDA_append_token(temp, temp_index, i);
            LAMBDA_add_to_token(temp, temp_index, c);
            LAMBDA_append_token(temp, temp_index, i);
            continue;
        }
add_char:
        LAMBDA_add_to_token(temp, temp_index, c);
        continue;
    }
    // LAMBDA_append_token(temp, temp_index);

    // for (size_t i = 0; i<num_tokens; i++) {
    //     print_token(tks+i);
    // }

    (*tokens) = (Token*)malloc(sizeof(Token)*num_tokens);
    memcpy(*tokens, tks, sizeof(Token)*num_tokens);

    return num_tokens;
}

void print_token(const Token* tok) {
    printf("%s:%3zu:%-3zu: `%s`\n", tok->parent.file_path,
            tok->parent.line_num+1, tok->offset, tok->txt);
}