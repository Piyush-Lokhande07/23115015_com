#include "codegen.h"

void generate(ASTNode *node)
{
      switch (node->type)
      {
      case AST_INT:
            printf("  movl $%d, %%eax\n", node->value);
            break;
      case AST_RETURN:
            generate(node->left);
            printf("  ret\n");
            break;
      }
}
