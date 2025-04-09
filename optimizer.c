#include "optimizer.h"

void constant_folding(ASTNode *node)
{
      if (!node)
            return;
      constant_folding(node->left);
      constant_folding(node->right);

      if (node->type == AST_ADD &&
          node->left->type == AST_INT &&
          node->right->type == AST_INT)
      {
            node->type = AST_INT;
            node->value = node->left->value + node->right->value;
            free(node->left);
            free(node->right);
            node->left = NULL;
            node->right = NULL;
      }
}
