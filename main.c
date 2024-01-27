#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

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
  DOUBLE
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


TokenLiteral generate_number(char current, FILE *file){
  TokenLiteral number_token;
  number_token.type = INT; // to be changed -- if '.' encountered => decimal literal
  
  char* value = malloc(sizeof(char) * 8); //get entire number
  int index = 0;

  while(isdigit(current) && current != EOF){
    value[index] = current;
    index++;
    //printf("%c\n", current);
    current = fgetc(file);
  }
  value[index] = '\0';
  // printf("here is the number: %s\n", value);
  
  //convert the string to a number
  number_token.value = atoi(value); // convert value from string to int
  free(value);
  ungetc(current, file);
  return number_token;
}


void lexer(FILE * file){
  char current = fgetc(file); //* fgetc() returns int (ASCII val or EOF) + forwards internal file position indicator
  bool processed_number = false;
  
  while(current != EOF){
    
    if(current == '('){
      printf("FOUND OPEN PAREN\n");
    }
    else if(current == ')'){
      printf("FOUND CLOSING PAREN\n");
    }
    else if(current == ';'){
      printf("FOUND SEMI\n");
    }
    else if(isdigit(current)){
      TokenLiteral int_literal = generate_number(current, file);
      printf("FOUND INTEGER: %d\n", int_literal.value);
    }
    else if(isalpha(current)){
      printf("FOUND CHARACTER: %c\n", current);
    }

    if(processed_number == true) processed_number = false;    
    else current = fgetc(file);
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