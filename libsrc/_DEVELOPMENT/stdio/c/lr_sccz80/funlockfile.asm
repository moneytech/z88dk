
; void funlockfile(FILE *file)

XDEF funlockfile

funlockfile:

   push hl
   pop ix
   
   INCLUDE "stdio/z80/asm_funlockfile.asm"
