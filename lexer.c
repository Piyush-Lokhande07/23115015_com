#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
      TOKEN_IDENTIFIER,
      TOKEN_REGISTER,
      TOKEN_diffsquare,
      TOKEN_UNKNOWN
} TokenType;

typedef struct
{
      TokenType type;
      char lexeme[32];
} Token;

int is_register(const char *word)
{
      return strcmp(word, "eax") == 0 || strcmp(word, "ebx") == 0;
}

Token *tokenize(const char *line, int *count)
{
      Token *tokens = malloc(3 * sizeof(Token));
      *count = 0;

      char temp[32];
      int i = 0, j = 0;

      while (line[i])
      {
            if (isspace(line[i]))
            {
                  i++;
                  continue;
            }

            j = 0;
            while (line[i] && !isspace(line[i]) && line[i] != ',')
            {
                  temp[j++] = line[i++];
            }
            temp[j] = '\0';

            if (strcmp(temp, "diffsquare") == 0)
            {
                  tokens[*count].type = TOKEN_diffsquare;
            }
            else if (is_register(temp))
            {
                  tokens[*count].type = TOKEN_REGISTER;
            }
            else
            {
                  tokens[*count].type = TOKEN_IDENTIFIER;
            }

            strncpy(tokens[*count].lexeme, temp, sizeof(tokens[*count].lexeme));
            (*count)++;

            if (line[i] == ',')
                  i++;
      }

      return tokens;
}
