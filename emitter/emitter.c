#include "emitter.h"

void emit_instruction(FILE *f, uint8_t opcode, int value)
{
      fwrite(&opcode, 1, 1, f);
      fwrite(&value, 4, 1, f);
}

void emit_return(FILE *f)
{
      uint8_t opcode = 0xc3;
      fwrite(&opcode, 1, 1, f);
}
