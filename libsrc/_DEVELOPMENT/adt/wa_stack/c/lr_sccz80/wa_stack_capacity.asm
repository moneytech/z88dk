
; size_t wa_stack_capacity(wa_stack_t *s)

XDEF wa_stack_capacity

;defc wa_stack_capacity = asm_wa_stack_capacity

wa_stack_capacity:

   INCLUDE "adt/wa_stack/z80/asm_wa_stack_capacity.asm"
