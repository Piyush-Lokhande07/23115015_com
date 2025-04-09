#ifndef LEXER_H
#define LEXER_H

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

Token *tokenize(const char *line, int *count);

#endif
