#include <stdio.h>
#include "lexer.h"
#include "parser.h"

extern void assemble_diffsquare(diffsquareInstruction *instr, FILE *out);

int main()
{
      const char *code = "diffsquare eax, ebx";
      int token_count = 0;

      Token *tokens = tokenize(code, &token_count);
      diffsquareInstruction *instr = parse_diffsquare(tokens, token_count);

      if (instr)
      {
            FILE *out = fopen("diffsquare_code.bin", "wb");
            assemble_diffsquare(instr, out);
            fclose(out);
      }

      free(tokens);
      free(instr);
      return 0;
}
