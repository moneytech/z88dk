/*
     ZZZZZZZZZZZZZZZZZZZZ    8888888888888       00000000000
   ZZZZZZZZZZZZZZZZZZZZ    88888888888888888    0000000000000
                ZZZZZ      888           888  0000         0000
              ZZZZZ        88888888888888888  0000         0000
            ZZZZZ            8888888888888    0000         0000       AAAAAA         SSSSSSSSSSS   MMMM       MMMM
          ZZZZZ            88888888888888888  0000         0000      AAAAAAAA      SSSS            MMMMMM   MMMMMM
        ZZZZZ              8888         8888  0000         0000     AAAA  AAAA     SSSSSSSSSSS     MMMMMMMMMMMMMMM
      ZZZZZ                8888         8888  0000         0000    AAAAAAAAAAAA      SSSSSSSSSSS   MMMM MMMMM MMMM
    ZZZZZZZZZZZZZZZZZZZZZ  88888888888888888    0000000000000     AAAA      AAAA           SSSSS   MMMM       MMMM
  ZZZZZZZZZZZZZZZZZZZZZ      8888888888888       00000000000     AAAA        AAAA  SSSSSSSSSSS     MMMM       MMMM

Copyright (C) Gunther Strube, InterLogic 1993-99
Copyright (C) Paulo Custodio, 2011-2014

$Header: /home/dom/z88dk-git/cvs/z88dk/src/z80asm/Attic/z80instr.c,v 1.93 2014-12-29 18:16:41 pauloscustodio Exp $
*/

#include "xmalloc.h"   /* before any other include */

#include "codearea.h"
#include "errors.h"
#include "expr.h"
#include "options.h"
#include "scan.h"
#include "symbol.h"
#include "z80asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* local functions */
void IncDec_8bit_instr( int opcode );

void
OUT( void )
{
	GetSym();
	
	if (opts.cpu & CPU_RABBIT)
	{
		error_illegal_ident();
	}
	else
	{
		switch (sym.tok)
		{
		case TK_IND_C:							/* OUT (C), r */
			GetSymExpect(TK_COMMA);
			GetSym();
			if (sym.cpu_reg8 != REG_NONE && !sym.cpu_idx_reg)
				append_2bytes(0xED, (Byte)(0x41 + (sym.cpu_reg8 << 3)));
			else
			{
				error_illegal_ident();
			
			}
			break;

		case TK_LPAREN:							/* OUT (N), A */
			GetSym();
			append_byte(0xD3);
			if (!Pass2info(RANGE_BYTE_UNSIGNED))
				return;							/* error in expression */

			if (sym.tok != TK_RPAREN)
			{
				error_syntax();
			}

			GetSymExpect(TK_COMMA);
			GetSym();
			if (sym.tok != TK_A)
			{
				error_illegal_ident();
			}

			break;

		default:
			break;
		}
	}
}


void CALL_OZ( void )
{
    long constant;

    append_byte( 0xE7 );          /* RST 20H instruction */

    GetSym();

	if ( expr_parse_eval( &constant ) )
	{
        if ( ( constant > 0 ) && ( constant <= 255 ) )
        {
            append_byte( (Byte)constant ); /* 1 byte OZ parameter */
        }
        else if ( ( constant > 255 ) && ( constant <= 65535 ) )
        {
            append_word( constant );  /* 2 byte OZ parameter */
        }
        else
        {
            error_int_range( constant );
        }
    }
}


void OZ( void )
{
    CALL_OZ();
}


void
CALL_PKG( void )
{
    long constant;

    append_byte( 0xCF );          /* RST 08H instruction */

	GetSym();

	if ( expr_parse_eval( &constant ) )
	{
        if ( ( constant >= 0 ) && ( constant <= 65535 ) )
        {
            append_word( constant );    /* 2 byte parameter always */
        }
        else
        {
            error_int_range( constant );
        }
    }
}

void
INVOKE( void )
{
    long constant;

    if ( opts.ti83plus )
        append_byte( 0xEF );    /* Ti83Plus: RST 28H instruction */
    else
        append_byte( 0xCD );    /* Ti83: CALL */

	GetSym();

	if ( expr_parse_eval( &constant ) )
	{
        if ( ( constant >= 0 ) && ( constant <= 65535 ) )
        {
            append_word( constant );    /* 2 byte parameter always */
        }
        else
        {
            error_int_range( constant );
        }
    }
}

void
FPP( void )
{
    long constant;

    append_byte( 0xDF );          /* RST 18H instruction */

	GetSym();

	if ( expr_parse_eval( &constant ) )
	{
        if ( ( constant > 0 ) && ( constant < 255 ) )
        {
            append_byte( (Byte)constant ); /* 1 byte OZ parameter */
        }
        else
        {
            error_int_range( constant );
        }
    }
}

static void INC_DEC(int opcode8bit, int opcode16bit)
{
	GetSym();

	switch (sym.cpu_reg16_sp)
	{
	case REG_NONE:
		IncDec_8bit_instr(opcode8bit);   /* 16 bit register wasn't found - try to evaluate the 8bit version */
		break;

	default:
		if (sym.cpu_idx_reg)
			append_byte(sym.cpu_idx_reg);

		append_byte((Byte)(opcode16bit + (sym.cpu_reg16_sp << 4)));
	}

}

void
INC( void )
{
	INC_DEC(4, 0x03);
}

void
DEC( void )
{
	INC_DEC(5, 0x0B);
}

void
IncDec_8bit_instr(int opcode)
{
	if (sym.cpu_ind_reg16 == IND_REG16_HL)							/* (hl), (ix+d), (iy+d) */
	{
		if (sym.cpu_idx_reg)
			append_byte(sym.cpu_idx_reg);

		append_byte((Byte)(0x30 + opcode));		/* INC/DEC (HL) */

		if (sym.cpu_idx_reg)
		{
			GetSym();
			Pass2info(RANGE_BYTE_SIGNED);
		}
	}
	else if (sym.cpu_reg8 != REG_NONE)
	{
		/* no indirect addressing, must be an 8bit register */
		if (sym.cpu_idx_reg)
		{
			if (opts.cpu & CPU_RABBIT)
			{
				error_illegal_ident();
				return;
			}
			append_byte(sym.cpu_idx_reg);
		}

		append_byte((Byte)((sym.cpu_reg8 << 3) + opcode));			/* INC/DEC  r */
	}
	else
	{
		error_syntax();
	}
}

void
BitTest_instr( int opcode )
{
    long bitnumber;

    GetSym();

	if (!expr_parse_eval(&bitnumber))
		return;

	if (bitnumber < 0 || bitnumber > 7)
	{
		error_int_range(bitnumber);
		return;
	}

	CurSymExpect(TK_COMMA);
	GetSym();

	if (sym.cpu_ind_reg16 == IND_REG16_HL)							/* (hl), (ix+d), (iy+d) */
	{
		if (!sym.cpu_idx_reg)
			append_2bytes(0xCB, (Byte)(opcode + (bitnumber << 3) + 0x06));
		else
		{
			append_2bytes(sym.cpu_idx_reg, 0xCB);
			GetSym();
			Pass2info(RANGE_BYTE_SIGNED);
			append_byte((Byte)(opcode + (bitnumber << 3) + 0x06));
		}
	}
	else if (sym.cpu_reg8 != REG_NONE)
	{
		/* no indirect addressing, must be an 8bit register */
		if (sym.cpu_idx_reg)
		{
			error_illegal_ident();
		}
		else
			append_2bytes(0xCB, (Byte)(opcode + (bitnumber << 3) + sym.cpu_reg8));
	}
	else
	{
		error_illegal_ident();
	}
}


void
RotShift_instr( int opcode )
{
	GetSym();

	if (sym.cpu_ind_reg16 == IND_REG16_HL)							/* (hl), (ix+d), (iy+d) */
	{
		if (!sym.cpu_idx_reg)
			append_2bytes(0xCB, (Byte)((opcode << 3) + 0x06));
		else
		{
			append_2bytes(sym.cpu_idx_reg, 0xCB);
			GetSym();
			Pass2info(RANGE_BYTE_SIGNED);
			append_byte((Byte)((opcode << 3) + 0x06));
		}
	}
	else if (sym.cpu_reg8 != REG_NONE)
	{
		/* no indirect addressing, must be an 8bit register */
		if (sym.cpu_idx_reg)
		{
			error_illegal_ident();
		}
		else
			append_2bytes(0xCB, (Byte)((opcode << 3) + sym.cpu_reg8));
	}
	else
	{
		error_illegal_ident();
	}
}
