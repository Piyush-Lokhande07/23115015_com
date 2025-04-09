#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int extract_value(const char *line, const char *var)
{
      char *p = strstr(line, var);
      if (!p)
            return 0;
      p = strchr(p, '=');
      if (!p)
            return 0;
      return atoi(p + 1);
}

int main()
{
      FILE *in = fopen("main.c", "r");
      FILE *out = fopen("out.s", "w");

      char line[256];
      int a_val = 0, b_val = 0;
      char expr_line[256] = "";

      while (fgets(line, sizeof(line), in))
      {
            if (strstr(line, "int a"))
                  a_val = extract_value(line, "a");
            else if (strstr(line, "int b"))
                  b_val = extract_value(line, "b");
            else if (strstr(line, "return"))
                  strcpy(expr_line, line);
      }

      fprintf(out,
              ".section __TEXT,__text,regular,pure_instructions\n"
              ".globl _main\n"
              "_main:\n"
              "    movl $%d, %%eax\n"
              "    movl $%d, %%ebx\n",
              a_val, b_val);

      if (strstr(expr_line, "(a + b) * (a - b)"))
      {
            fprintf(out, "    .byte 0x0f, 0xaa  ## diffsquare\n");
      }
      else
      {
            fprintf(out,
                    "    addl %%ebx, %%eax\n"
                    "    subl %%ebx, %%eax\n"
                    "    imull %%ebx, %%eax\n");
      }

      fprintf(out, "    ret\n");

      fclose(in);
      fclose(out);
      printf("✅ Generated 'out.s' with a=%d, b=%d\n", a_val, b_val);
      return 0;
}
