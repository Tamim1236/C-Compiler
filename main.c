#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "lexer.h"

int main(){
  FILE *file = fopen("test.unn", "r");
  
  if(file == NULL){
    printf("Error opening file\n");
    return 1;
  }
  
  Token *tokens = malloc(sizeof(Token)*12);
  int* tokens_len = malloc(sizeof(int));
  *tokens_len = 0;
  lexer(file, tokens, tokens_len);

  print_all_tokens(tokens, *tokens_len);

  //cleanup_all_tokens(tokens, *tokens_len);
  fclose(file);
  return 0;
}