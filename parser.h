#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct
{
      char dest[8];
      char src[8];
} diffsquareInstruction;

diffsquareInstruction *parse_diffsquare(Token *tokens, int count);

#endif
