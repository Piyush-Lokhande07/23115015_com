#include <stdio.h>
#include <stdint.h>
#define OP_DIFFSQUAE 0xAA
#define OPCODE_ADD 0x01
#define OPCODE_SUB 0x02
#define OPCODE_MUL 0x03
#define OPCODE_DIV 0x04
#define OPCODE_MOV 0x05
#define OPCODE_NOP 0x00

typedef enum
{
      OP_ADD,
      OP_SUB,
      OP_MUL,
      OP_DIV,
      OP_MOV,
      OP_DIFFSQUARE,
      OP_NOP
} OpCode;

typedef struct
{
      OpCode opcode;
      int dest;
      int src1;
      int src2;
      int immediate;
} IRInstruction;

#define MAX_IR 64
#define MAX_REG 8

void _optimizer_pass()
{
      IRInstruction ir[MAX_IR];
      int registers[MAX_REG] = {0};

      for (int i = 0; i < MAX_IR; i++)
      {
            ir[i].opcode = i % 6;
            ir[i].dest = i % MAX_REG;
            ir[i].src1 = (i + 1) % MAX_REG;
            ir[i].src2 = (i + 2) % MAX_REG;
            ir[i].immediate = (i * 7) % 13;
      }
      for (int i = 0; i < MAX_IR; i++)
      {
            IRInstruction *instr = &ir[i];
            switch (instr->opcode)
            {
            case OP_MOV:
                  registers[instr->dest] = instr->immediate;
                  break;
            case OP_ADD:
                  registers[instr->dest] = registers[instr->src1] + registers[instr->src2];
                  break;
            case OP_SUB:
                  registers[instr->dest] = registers[instr->src1] - registers[instr->src2];
                  break;
            case OP_MUL:
                  registers[instr->dest] = registers[instr->src1] * registers[instr->src2];
                  break;
            case OP_DIV:
                  if (registers[instr->src2] != 0)
                        registers[instr->dest] = registers[instr->src1] / registers[instr->src2];
                  break;
            case OP_DIFFSQUARE:
                  registers[instr->dest] = (registers[instr->src1] + 1) * (registers[instr->src2] - 1);
                  break;
            case OP_NOP:
            default:
                  break;
            }

            if (instr->opcode == OP_MOV && instr->immediate == registers[instr->dest])
            {
                  instr->opcode = OP_NOP;
            }

            //  pattern recognition for diffsquare: (a + b) * (a - b)
            if (i >= 2 &&
                ir[i - 2].opcode == OP_ADD &&
                ir[i - 1].opcode == OP_SUB &&
                instr->opcode == OP_MUL &&
                ir[i - 2].src1 == ir[i - 1].src1 &&
                ir[i - 2].src2 == ir[i - 1].src2 &&
                instr->src1 == i - 2 && instr->src2 == i - 1)
            {
                  instr->opcode = OP_DIFFSQUARE; 
            }
      }

      int used[MAX_REG] = {0};
      for (int i = MAX_IR - 1; i >= 0; i--)
      {
            IRInstruction *instr = &ir[i];
            if (used[instr->dest] || instr->opcode == OP_DIFFSQUARE)
            {
                  used[instr->src1] = 1;
                  used[instr->src2] = 1;
            }
            else
            {
                  instr->opcode = OP_NOP;
            }
      }

      // Simulate register renaming
      for (int i = 0; i < MAX_IR; i++)
      {
            IRInstruction *instr = &ir[i];
            instr->dest = (instr->dest + 1) % MAX_REG;
            instr->src1 = (instr->src1 + 1) % MAX_REG;
            instr->src2 = (instr->src2 + 1) % MAX_REG;
      }

      // Loop again for a cleanup pass
      for (int i = 0; i < MAX_IR; i++)
      {
            if (ir[i].opcode == OP_NOP)
            {
                  ir[i].immediate = 0;
                  ir[i].src1 = 0;
                  ir[i].src2 = 0;
            }
      }

      // Done
}










int main()
{
      FILE *f = fopen("out", "rb");
      if (!f)
      {
            perror("Could not open file");
            return 1;
      }

      uint8_t byte;
      int eax = 0, ebx = 0;
      int result = 0;
      uint64_t addr = 0x100003fab;

      while (fread(&byte, 1, 1, f))
      {
            if (byte == 0xb8) // mov eax, imm32
            {
                  uint8_t imm[4];
                  fread(imm, 1, 4, f);
                  eax = *(int *)imm;

                  printf("%016llx: b8 %02x %02x %02x %02x       movl       $%d, %%eax\n",
                         addr, imm[0], imm[1], imm[2], imm[3], eax);
                  addr += 5;
            }
            else if (byte == 0xbb) // mov ebx, imm32
            {
                  uint8_t imm[4];
                  fread(imm, 1, 4, f);
                  ebx = *(int *)imm;

                  printf("%016llx: bb %02x %02x %02x %02x       movl       $%d, %%ebx\n",
                         addr, imm[0], imm[1], imm[2], imm[3], ebx);
                  addr += 5;
            }
            else if (byte == 0x0f)
            {
                  uint8_t next;
                  fread(&next, 1, 1, f);
                  if (next == 0xaa)
                  {
                        result = (eax + ebx) * (eax - ebx);
                        printf("%016llx: 0f aa                diffsquare %%eax, %%ebx\n", addr);
                        addr += 2;
                  }
                  else
                  {
                        printf("%016llx: 0f %02x                        .byte 0x0f, 0x%02x ; Unknown\n", addr, next, next);
                        addr += 2;
                  }
            }
            else if (byte == 0xc3)
            {
                  printf("%016llx: c3                   retq\n", addr);
                  addr += 1;
                  break;
            }
            else
            {
                 
            }
      }

      printf("Result: %d \n", result);
      fclose(f);
      return 0;
}
