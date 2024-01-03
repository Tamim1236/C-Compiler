#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// we start with just the exit(1);

//* ISSUES TO FIX:
//* - can only process single digits for literal values => exit(42) processes as "...4, 2, )"

// define enums
typedef enum{
  EXIT,
} TypeKeyword;

typedef enum{
  SEMI,
  OPEN_PAREN,
  CLOSE_PAREN,
} TypeSeperator;

typedef enum{
  INT,
} TypeLiteral;


//define structs
typedef struct{
  TypeKeyword type;
} TokenKeyword;

typedef struct{
  TypeSeperator type;
} TokenSeperator;

typedef struct{
  TypeLiteral type;
  int value;
} TokenLiteral;

void generate_nuimber(char current, FILE *file){
  while(current != EOF){
    printf("%c\n", current);
    current = fgetc(file);
  }
}


void lexer(FILE * file){
  char current = fgetc(file);

  while(current != EOF){
    if(current == ';'){
      printf("FOUND SEMI\n ");
    }else if(current == '('){
      printf("FOUND OPEN PAREN\n");
    }else if(current == ')'){
      printf("FOUND CLOSING PAREN\n");
    }else if(isdigit(current)){
      printf("FOUND DIGIT: %c\n", current);
    }else if(isalpha(current)){
      printf("FOUND CHARACTER: %c\n", current);
    }

    // printf("%c\n", current);
    current = fgetc(file);
  }
}


int main(){
  FILE *file;
  file = fopen("test.unn", "r");
  
  lexer(file);

  // TokenLiteral token;
  // token.type = INT;
  // token.value = 5;
  // printf("%d\n", token.value);
}