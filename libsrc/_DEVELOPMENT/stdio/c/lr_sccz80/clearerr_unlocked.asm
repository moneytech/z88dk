
; void clearerr_unlocked(FILE *stream)

XDEF clearerr_unlocked

clearerr_unlocked:

   push hl
   pop ix
   
   INCLUDE "stdio/z80/asm_clearerr_unlocked.asm"
