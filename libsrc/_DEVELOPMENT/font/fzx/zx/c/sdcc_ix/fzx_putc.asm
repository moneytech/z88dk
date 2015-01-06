
; int fzx_putc(struct fzx_state *fs, int c)

SECTION code_font_fzx

PUBLIC _fzx_putc

_fzx_putc:

   pop af
   pop hl
   pop bc
   
   push bc
   push hl
   push af
   
   push hl
   ex (sp),ix

   call asm_fzx_putc
   
   pop ix
   ret nc
   
   ld l,a
   ld h,0
   
   ret
   
   INCLUDE "font/fzx/zx/z80/asm_fzx_putc.asm"
