
; ===============================================================
; Dec 2013
; ===============================================================
; 
; int obstack_grow(struct obstack *ob, void *data, size_t size)
;
; Grow the current object by appending size bytes read from
; address data.
;
; ===============================================================

XDEF obstack_grow_callee

obstack_grow_callee:

   pop hl
   pop bc
   pop de
   ex (sp),hl
   
   INCLUDE "alloc/obstack/z80/asm_obstack_grow.asm"
