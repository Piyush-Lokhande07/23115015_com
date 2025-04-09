#include <stdlib.h>
#include <string.h>
#include "lexer.h"

typedef struct
{
      char dest[8];
      char src[8];
} diffsquareInstruction;

diffsquareInstruction *parse_diffsquare(Token *tokens, int count)
{
      if (count != 3 || tokens[0].type != TOKEN_diffsquare)
            return NULL;

      diffsquareInstruction *instr = malloc(sizeof(diffsquareInstruction));
      strncpy(instr->dest, tokens[1].lexeme, sizeof(instr->dest));
      strncpy(instr->src, tokens[2].lexeme, sizeof(instr->src));
      return instr;
}
