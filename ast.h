#ifndef AST_H
#define AST_H

typedef enum
{
      AST_ADD,
      AST_SUB,
      AST_MUL,
      AST_VAR,
      AST_CONST
} ASTType;

typedef struct ASTNode
{
      ASTType type;
      char var; 
      struct ASTNode *left;
      struct ASTNode *right;
} ASTNode;

#endif
