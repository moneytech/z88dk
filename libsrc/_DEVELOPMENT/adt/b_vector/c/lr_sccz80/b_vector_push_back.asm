
; size_t b_vector_push_back(b_vector_t *v, int c)

XDEF b_vector_push_back

LIB b_vector_append

;defc b_vector_push_back = b_vector_append

b_vector_push_back:

   jp b_vector_append
