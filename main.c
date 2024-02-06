#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "lexer.h"
#include "parser.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("ERROR - proper syntax is ./%s <filename.unn>\n", argv[0]);
    exit(1);
  }
  
  FILE *file = fopen(argv[1], "r");
  
  if(file == NULL){
    printf("Error opening file named %s\n", argv[1]);
    return 1;
  }
  
  Token *tokens = malloc(sizeof(Token)*12);
  int* tokens_len = malloc(sizeof(int));
  *tokens_len = 0;
  lexer(file, tokens, tokens_len);

  print_all_tokens(tokens, *tokens_len);

  printf("HELLO?\n");
  parser(tokens, *tokens_len);
  printf("WERE BACK?\n");

  //cleanup_all_tokens(tokens, *tokens_len);
  fclose(file);
  return 0;
}