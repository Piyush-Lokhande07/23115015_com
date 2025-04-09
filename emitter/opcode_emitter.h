#include "opcode_emitter.h"
#include <stdio.h>

void emit_opcode(OpType op, char reg1, char reg2)
{
      switch (op)
      {
      case OP_DIFFSQUARE:
            printf("Emitting opcode 0F AA for diffsquare with %c, %c\n", reg1, reg2);
            emit_byte(0x0f);
            emit_byte(0xaa);
            break;
      default:
            printf("Unknown opcode\n");
            break;
      }
}

void emit_byte(unsigned char byte)
{
      FILE *f = fopen("out", "ab");
      fwrite(&byte, 1, 1, f);
      fclose(f);
}
