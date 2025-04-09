#include "tokenizer.h"
#include <ctype.h>
#include <string.h>

Token tokens[MAX_TOKENS];
int token_count = 0;

void tokenize(const char *src)
{
      int i = 0;
      while (*src)
      {
            if (isspace(*src))
            {
                  src++;
            }
            else if (isdigit(*src))
            {
                  int value = 0;
                  while (isdigit(*src))
                  {
                        value = value * 10 + (*src - '0');
                        src++;
                  }
                  tokens[token_count++] = (Token){TOKEN_INT, value};
            }
            else if (isalpha(*src))
            {
                  char ident[32] = {0};
                  int j = 0;
                  while (isalnum(*src))
                  {
                        ident[j++] = *src++;
                  }
                  if (strcmp(ident, "return") == 0)
                        tokens[token_count++] = (Token){TOKEN_RETURN};
                  else
                        tokens[token_count++] = (Token){TOKEN_IDENT, 0, strdup(ident)};
            }
            else
            {
                  switch (*src)
                  {
                  case '+':
                        tokens[token_count++] = (Token){TOKEN_PLUS};
                        break;
                  case '-':
                        tokens[token_count++] = (Token){TOKEN_MINUS};
                        break;
                  case '*':
                        tokens[token_count++] = (Token){TOKEN_MUL};
                        break;
                  case '/':
                        tokens[token_count++] = (Token){TOKEN_DIV};
                        break;
                  case ';':
                        tokens[token_count++] = (Token){TOKEN_SEMI};
                        break;
                  }
                  src++;
            }
      }
}
