#include "ast.h"
#include "opcode_emitter.h"
#include <stdbool.h>

bool is_diff_square_pattern(ASTNode *node)
{
      if (!node || node->type != AST_MUL)
            return false;

      ASTNode *left = node->left;
      ASTNode *right = node->right;

      if (!left || !right)
            return false;

      return (left->type == AST_ADD && right->type == AST_SUB) &&
             ((left->left->var == right->left->var && left->right->var == right->right->var) ||
              (left->left->var == right->right->var && left->right->var == right->left->var));
}

void analyze_and_emit(ASTNode *root)
{
      if (is_diff_square_pattern(root))
      {
            emit_opcode(OP_diffsquare, root->left->left->var, root->left->right->var);
      }
      else
      {
            // Fallback to generic emit
            default_emit(root);
      }
}
