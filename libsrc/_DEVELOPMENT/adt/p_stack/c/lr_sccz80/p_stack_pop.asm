
; void *p_stack_pop(p_stack_t *s)

XDEF p_stack_pop

;defc p_stack_pop = asm_p_stack_pop

p_stack_pop:

   INCLUDE "adt/p_stack/z80/asm_p_stack_pop.asm"
