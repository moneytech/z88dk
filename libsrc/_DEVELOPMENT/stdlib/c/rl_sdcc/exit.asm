
; _Noreturn void exit(int status)

XDEF exit

exit:

   pop af
   pop hl
   
   push hl
   push af
   
   INCLUDE "stdlib/z80/asm_exit.asm"
