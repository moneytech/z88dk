
; void *p_forward_list_insert_after(void *list_item, void *item)

XDEF p_forward_list_insert_after_callee

p_forward_list_insert_after_callee:

   pop hl
   pop de
   ex (sp),hl
   
   INCLUDE "adt/p_forward_list/z80/asm_p_forward_list_insert_after.asm"
