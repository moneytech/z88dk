
; void bv_priority_queue_clear(bv_priority_queue_t *q)

XDEF bv_priority_queue_clear

;defc bv_priority_queue_clear = asm_bv_priority_queue_clear

bv_priority_queue_clear:

   INCLUDE "adt/bv_priority_queue/z80/asm_bv_priority_queue_clear.asm"
