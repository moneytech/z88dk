
; _Noreturn void quick_exit(int status)

XDEF quick_exit

quick_exit:

   pop af
   pop hl
   
   push hl
   push af
   
   INCLUDE "stdlib/z80/asm_quick_exit.asm"
