
; uchar zx_aaddr2py(void *attraddr)

SECTION code_clib
SECTION code_arch

PUBLIC zx_aaddr2py

EXTERN asm_zx_aaddr2py

defc zx_aaddr2py = asm_zx_aaddr2py

; SDCC bridge for Classic
IF __CLASSIC
PUBLIC _zx_aaddr2py
defc _zx_aaddr2py = zx_aaddr2py
ENDIF

