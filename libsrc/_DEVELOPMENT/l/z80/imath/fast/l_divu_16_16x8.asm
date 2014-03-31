
XLIB l_divu_16_16x8
XDEF l0_divu_16_16x8

LIB l0_divu_8_8x8, error_divide_by_zero_mc

l_divu_16_16x8:

   ; unsigned division of a 16-bit dividend
   ; by an 8-bit divisor
   ;
   ; enter : hl = 16-bit dividend
   ;          e = 8-bit divisor
   ;
   ; exit  : d = 0
   ;
   ;         success
   ;
   ;             a = 0
   ;            hl = hl / e
   ;             e = hl % e
   ;            carry reset
   ;
   ;         divide by zero
   ;
   ;            hl = $ffff = UINT_MAX
   ;            de = dividend
   ;            carry set, errno = EDOM
   ;
   ; uses  : af, b, de, hl

   ; test for divide by zero
   
   inc e
   dec e
   jr z, divide_by_zero

l0_divu_16_16x8:

   ; try to reduce the division
   
   inc h
   dec h
   jp z, l0_divu_8_8x8

   xor a
   ld d,a

   ; unroll divide eight times
   
   ld b,2

   ; eliminate leading zeroes

loop_00:

   add hl,hl
   jr c, loop_10

   add hl,hl
   jr c, loop_20

   add hl,hl
   jr c, loop_30

   add hl,hl
   jr c, loop_40

   add hl,hl
   jr c, loop_50

   add hl,hl
   jr c, loop_60

   add hl,hl
   jr c, loop_70

   add hl,hl
   rla
   
   cp e
   jr c, loop_80
   
   sub e
   inc l

loop_80:

   dec b
   
   ; general divide loop

loop_0:

   add hl,hl
   
loop_10:

   rla
   jr c, loop_101
   
   cp e
   jr c, loop_1

loop_101:

   sub e
   inc l

loop_1:

   add hl,hl

loop_20:

   rla
   jr c, loop_201
   
   cp e
   jr c, loop_2

loop_201:

   sub e
   inc l

loop_2:

   add hl,hl

loop_30:

   rla
   jr c, loop_301
   
   cp e
   jr c, loop_3

loop_301:
   
   sub e
   inc l

loop_3:

   add hl,hl

loop_40:

   rla
   jr c, loop_401
   
   cp e
   jr c, loop_4

loop_401:

   sub e
   inc l

loop_4:

   add hl,hl

loop_50:

   rla
   jr c, loop_501
   
   cp e
   jr c, loop_5

loop_501:

   sub e
   inc l

loop_5:

   add hl,hl

loop_60:

   rla
   jr c, loop_601
   
   cp e
   jr c, loop_6

loop_601:

   sub e
   inc l

loop_6:

   add hl,hl

loop_70:

   rla
   jr c, loop_701
   
   cp e
   jr c, loop_7

loop_701:
   
   sub e
   inc l

loop_7:

   add hl,hl
   rla
   jr c, loop_801
   
   cp e
   jr c, loop_8

loop_801:
   
   sub e
   inc l

loop_8:

   djnz loop_0

exit_loop:

   ;  a = remainder
   ; hl = quotient

   ld e,a
   
   xor a
   ret

divide_by_zero:

   ex de,hl
   jp error_divide_by_zero_mc
