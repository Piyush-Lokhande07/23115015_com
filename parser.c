#include "parser.h"

ASTNode *parse_expr(int *i)
{
      if (tokens[*i].type == TOKEN_INT)
      {
            ASTNode *node = malloc(sizeof(ASTNode));
            node->type = AST_INT;
            node->value = tokens[*i].value;
            (*i)++;
            return node;
      }

      if (tokens[*i].type == TOKEN_IDENT)
      {
            ASTNode *node = malloc(sizeof(ASTNode));
            node->type = AST_VAR;
            node->name = tokens[*i].str;
            (*i)++;
            return node;
      }

      return NULL;
}

ASTNode *parse_return_stmt(int *i)
{
      (*i)++; // Skip 'return'
      ASTNode *expr = parse_expr(i);
      if (tokens[*i].type != TOKEN_SEMI)
      {
            printf("Expected ';'\n");
            exit(1);
      }
      (*i)++;
      ASTNode *node = malloc(sizeof(ASTNode));
      node->type = AST_RETURN;
      node->left = expr;
      return node;
}
