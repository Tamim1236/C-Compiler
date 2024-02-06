#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

typedef struct Node{
 char *value;
 TokenType type;
 struct Node *left;
 struct Node *right;
} Node;

Node *init_node(Node *node, char *value, TokenType type){
  node = malloc(sizeof(Node));
  node->value = malloc(sizeof(char) * 2); 
  node->value = value;
  node->type = type;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void print_tree(Node *node){
  if(node == NULL){
    return;
  }

  printf("    %s\n", node->value);
  print_tree(node->left);
  print_tree(node->right);
}


Token *parser(Token *tokens/*, int* tokens_len*/){
  printf("ENTERING THE PARSER FUNCTION\n");
  //printf("ayo the token length is %d\n", *tokens_len);
  Token *current_token = &tokens[0];
  printf("HMM???\n");
  Node *root = malloc(sizeof(Node));
  root = init_node(root, "PROGRAM", BEGINNING);
  Node *curr = root; // current node in our tree
  
  //int i = 0; // num tokens seen
  //while(i < *tokens_len){
    //if(curr == NULL) break;
    
    if(curr == root) printf("ROOT\n");

    switch(current_token->type){
      case BEGINNING:
        break;
      case INT:
        break;
      case KEYWORD:
        if(strcmp(current_token->value, "exit")){
          Node *exit_node = malloc(sizeof(Node));
          exit_node = init_node(exit_node, current_token->value, KEYWORD);
          root->right = exit_node;
          
          curr = exit_node;
          current_token++;

          if(strcmp(current_token->value, "(") == 0 && current_token->type == SEPARATOR){
            Node *open_paren_node = malloc(sizeof(Node));
            open_paren_node = init_node(open_paren_node, current_token->value, SEPARATOR);

            curr->left = open_paren_node;
            current_token++;

            if(current_token->type == INT){
              Node *expression_node = malloc(sizeof(Node));
              expression_node = init_node(expression_node, current_token->value, INT);
              
              curr->left->left = expression_node;
              current_token++;

              if(strcmp(current_token->value, ")") == 0 && current_token->type == SEPARATOR){
                Node *close_paren_node = malloc(sizeof(Node));
                close_paren_node = init_node(close_paren_node, current_token->value, SEPARATOR);
                
                curr->left->right = close_paren_node;
                current_token++;

                if(strcmp(current_token->value, ";") == 0 && current_token->type == SEPARATOR){
                  Node* semi_node = malloc(sizeof(Node));
                  semi_node = init_node(semi_node, current_token->value, SEPARATOR);
                  curr->right = semi_node;
                  break;
                }
                else{
                  printf("ERROR: Invalid Syntax on SEMI\n");
                  exit(1);
                }
              }
              else{
                printf("ERROR: Invalid Syntax on CLOSE_PAREN\n");
                exit(1);
              }
            }
            else{
              printf("ERROR: Invalid Syntax on INT LITERAL\n");
              exit(1);
            }
          }
          else{
            printf("ERROR: Invalid Syntax on OPEN PAREN\n");
            exit(1);
          }
        }
        current_token++;
        break;
      
      case SEPARATOR:
        break;
    }

      print_tree(root);

      printf("EXIT\n");
      //break;
      //printf("ayo the token length is %d\n", *tokens_len);
    //}


  return current_token;
}