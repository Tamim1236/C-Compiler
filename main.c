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


int generate_number(char current, FILE *file){
  int* number = NULL; // dynamic array
  int allocated_size = 2; //space for 1-digit number (with '\0' at end)
  number[allocated_size - 1] = '\0';
  int curr_len = 1; //track current length of number (current number of digits seen)
  
  while(isdigit(current)){
    printf("here is the current digit: %c\n", current);
    number[curr_len - 1] = current - '0'; // add digit to array
    
    if(curr_len + 1 == allocated_size){
      allocated_size *= 2;
      number = (int*) realloc(number, sizeof(int) * allocated_size);
      number[allocated_size - 1] = '\0';
    }
    
    //next char in file
    current = fgetc(file);
    curr_len += 1;
  }

  //convert int array into int and return
  int total = 0;
  for(int i = 0; i < curr_len - 1; i++){
    printf("Inside for loop with i = %d\n", i);
    // if(!number[i]){
    //   break;
    // }
    // else{
    total += number[i] * pow(10, curr_len-1 - i);
    // }
  }

  ungetc(current, file);
  return total;
}


void lexer(FILE * file){
  char current = fgetc(file); //* fgetc() returns int (ASCII val or EOF) + forwards internal file position indicator
  bool processed_number = false;
  
  while(current != EOF){
    if(current == ';'){
      printf("FOUND SEMI\n");
    }
    else if(current == '('){
      printf("FOUND OPEN PAREN\n");
    }
    else if(current == ')'){
      printf("FOUND CLOSING PAREN\n");
    }
    else if(isdigit(current)){
      int number = generate_number(current, file);
      printf("FOUND NUMBER: %d\n", number);
      processed_number = true;
      //printf("FOUND DIGIT: %c\n", current);
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