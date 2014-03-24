
; ===============================================================
; Dec 2013
; ===============================================================
; 
; void *obstack_next_free(struct obstack *ob)
;
; Returns address of next available byte in the obstack.
;
; ===============================================================

XDEF obstack_next_free

obstack_next_free:

   pop af
   pop hl
   
   push hl
   push af

   INCLUDE "alloc/obstack/z80/asm_obstack_next_free.asm"
