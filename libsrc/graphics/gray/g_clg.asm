;
;       TI Gray Library Functions
;
;       Written by Stefano Bodrato - Mar 2001
;
;

;Usage: g_clg()

		INCLUDE "graphics/grafix.inc"    /* Contains fn defs */

		XLIB    g_clg

		XREF	graybit1
		XREF	graybit2

.g_clg
	  	ld	hl,(graybit1)
	  	call	cls
	  	
	  	ld	hl,(graybit2)
.cls
		ld	(hl),0
		ld	d,h
		ld	e,l
		inc	de
		ld	bc,row_bytes*64
		ldir

		ret
