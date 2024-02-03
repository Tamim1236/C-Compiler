#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum{
  INT,
  KEYWORD,
  SEPARATOR,
}TokenType;

typedef struct{
  TokenType type;
  char *value;
} Token;

void print_token(Token* token){
  printf("TOKEN: %s\n", token->value);
  printf("TOKEN TYPE: ");
  if(token->type == INT) printf("INT\n");
  if(token->type == KEYWORD) printf("KEYWORD\n");
  if(token->type == SEPARATOR) printf("SEPARATOR\n");

  printf("\n");
}

void cleanup_token(Token* token){
  if(token != NULL){
    free(token->value);
    free(token);
  }
}


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


void lexer(FILE * file){
  char current; 
  
  //* fgetc() returns int (ASCII val or EOF) + forwards internal file position indicator
  while((current = fgetc(file)) != EOF){

    if(current == '('){
      Token* open_bracket_token = malloc(sizeof(Token));
      open_bracket_token->type = SEPARATOR;
      open_bracket_token->value = strdup("(");

      print_token(open_bracket_token);

      cleanup_token(open_bracket_token);
    }
    else if(current == ')'){
      Token* close_bracket_token = malloc(sizeof(Token));
      close_bracket_token->type = SEPARATOR;
      close_bracket_token->value = strdup(")");
      print_token(close_bracket_token);

      cleanup_token(close_bracket_token);
    }
    else if(current == ';'){
      Token* semicolon_token = malloc(sizeof(Token));
      semicolon_token->type = SEPARATOR;
      semicolon_token->value = strdup(";");
      print_token(semicolon_token);

      cleanup_token(semicolon_token);
    }
    else if(isdigit(current)){
      Token* int_literal = get_number(current, file);
      print_token(int_literal);

      cleanup_token(int_literal);
    }
    else if(isalpha(current)){
      Token* keyword = get_keyword(current, file);
      print_token(keyword);

      cleanup_token(keyword);
    }
  }
}


int main(){
  FILE *file = fopen("test.unn", "r");
  
  if(file == NULL){
    printf("Error opening file\n");
    return 1;
  }
  
  lexer(file);
  fclose(file);

  return 0;
}