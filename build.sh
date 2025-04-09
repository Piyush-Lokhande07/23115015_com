set -e

gcc compiler.c -o compiler
./compiler

as -o out.o out.s
ld -o out out.o -lSystem -syslibroot "$(xcrun --sdk macosx --show-sdk-path)" -e _main
gcc .internal/pass2_stage.c -o .internal/pass2_stage_exec #dissasembling
.internal/pass2_stage_exec

.internal/pass2_stage_exec > .internal/result.log


