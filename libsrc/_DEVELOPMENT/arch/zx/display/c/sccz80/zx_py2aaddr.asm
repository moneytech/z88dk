
; void *zx_py2aaddr(uchar y)

SECTION code_clib
SECTION code_arch

PUBLIC zx_py2aaddr

EXTERN asm_zx_py2aaddr

defc zx_py2aaddr = asm_zx_py2aaddr

; SDCC bridge for Classic
IF __CLASSIC
PUBLIC _zx_py2aaddr
defc _zx_py2aaddr = zx_py2aaddr
ENDIF

