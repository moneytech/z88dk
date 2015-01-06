
; char *fzx_buffer_partition_ww(struct fzx_font *ff, char *buf, uint16_t buflen, uint16_t allowed_width)

SECTION code_font_fzx

PUBLIC fzx_buffer_partition_ww_callee

fzx_buffer_partition_ww_callee:

   pop af
   pop hl
   pop bc
   pop de
   pop ix
   push af
   
   INCLUDE "font/fzx/z80/asm_fzx_buffer_partition_ww.asm"
