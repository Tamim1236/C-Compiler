#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "lexer.h"

Token *parser(Token *tokens, int token_len);

#endif