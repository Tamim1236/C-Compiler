#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

typedef enum{
  INT,
  KEYWORD,
  SEPARATOR,
}TokenType;

typedef struct{
  TokenType type;
  char *value;
} Token;

void print_token(Token* token);
void print_all_tokens(Token* tokens, int len);
void cleanup_token(Token* token);
Token *get_number(char current, FILE *file);
Token *get_keyword(char current, FILE * file);
void lexer(FILE *file, Token *tokens, int *len);

#endif