#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "lexer.h"

void print_token(Token* token){
  printf("TOKEN: %s\n", token->value);
  
  printf("TOKEN TYPE: ");
  switch(token->type){
    case BEGINNING:
      printf("BEGINNING\n");
      break;
    case INT:
      printf("INT\n");
      break;
    case KEYWORD:
      printf("KEYWORD\n");
      break;
    case SEPARATOR:
      printf("SEPARATOR\n");
      break;
  }
  
  printf("\n");
}

void print_all_tokens(Token* tokens, int len){
  printf("Lexer found %d tokens:\n", len);
  for(int i = 0; i < len; i++){
    print_token(&tokens[i]);
  }
}

void cleanup_token(Token* token){
  if(token != NULL){
    free(token->value);
    free(token);
  }
}

/*
void cleanup_all_tokens(Token* tokens, int len){
  for(int i = 0; i < len; i++){
    cleanup_token(&tokens[i]);
  }
  printf("Deleted all tokens\n"); // !? something wrong - this is not showing up in output
}
*/

Token* get_number(char current, FILE *file){
  Token* number_token = malloc(sizeof(Token));
  number_token->type = INT;
  
  char* value = malloc(sizeof(char) * 8); 
  int index = 0;

  while(isdigit(current) && current != EOF){
    value[index++] = current; 
    current = fgetc(file);
  }
  value[index] = '\0';
  
  number_token->value = value;

  ungetc(current, file); // push back the non-digit character
  return number_token;
}

Token *get_keyword(char current, FILE * file){
  Token* keyword_token = malloc(sizeof(Token));
  keyword_token->type = KEYWORD;
  
  char* keyword = malloc(sizeof(char) * 8);
  int index = 0;

  while(isalpha(current) && current != EOF){
    keyword[index++] = current;
    current = fgetc(file);
  }
  keyword[index] = '\0';

  if(strcmp(keyword, "exit") == 0){
    keyword_token->value = strdup("EXIT");
  }
  else{
    keyword_token->value = keyword; // directly assign the dynamically allocated keyword
  }
  
  ungetc(current, file);
  return keyword_token;
}


void lexer(FILE *file, Token *tokens, int *len){
  size_t tokens_i = 0;
  char current; 
  
  //* fgetc() returns int (ASCII val or EOF) + forwards internal file position indicator
  while((current = fgetc(file)) != EOF){

    if(current == '('){
      Token* open_bracket_token = malloc(sizeof(Token));
      open_bracket_token->type = SEPARATOR;
      open_bracket_token->value = strdup("("); //! DO I need to malloc() for the values as well or does strdup() cover it?

      //print_token(open_bracket_token);

      tokens[tokens_i++] = *open_bracket_token;
      //cleanup_token(open_bracket_token);
    }
    else if(current == ')'){
      Token* close_bracket_token = malloc(sizeof(Token));
      close_bracket_token->type = SEPARATOR;
      close_bracket_token->value = strdup(")");
      //print_token(close_bracket_token);

      tokens[tokens_i++] = *close_bracket_token;
      //cleanup_token(close_bracket_token);
    }
    else if(current == ';'){
      Token* semicolon_token = malloc(sizeof(Token));
      semicolon_token->type = SEPARATOR;
      semicolon_token->value = strdup(";");
      //print_token(semicolon_token);

      tokens[tokens_i++] = *semicolon_token;
      //cleanup_token(semicolon_token);
    }
    else if(isdigit(current)){
      Token* int_literal = get_number(current, file);
      //print_token(int_literal);

      tokens[tokens_i++] = *int_literal;
      //cleanup_token(int_literal);
    }
    else if(isalpha(current)){
      Token* keyword = get_keyword(current, file);
      //print_token(keyword);

      tokens[tokens_i++] = *keyword;
      //cleanup_token(keyword);
    }
    else{
      printf("ERROR: UNRECOGNIZED CHARACTER of -- %c --\n", current);
      exit(1);
    }
  }  
  *len = tokens_i; // final index is the length of the 'tokens' array
  //return tokens;
}