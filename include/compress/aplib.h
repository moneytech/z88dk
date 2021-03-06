


#ifndef __COMPRESS_APLIB_H__
#define __COMPRESS_APLIB_H__

//////////////////////////////////////////////////////////////////
//                      APLIB DECOMPRESSOR                      //
//////////////////////////////////////////////////////////////////
//                                                              //
// Z80 Decompressor by Maxim                                    //
// http://www.smspower.org/maxim/SMSSoftware/Compressors        //
//                                                              //
// Aplib Originally Created by Jorgen Ibsen                     //
// Copyright (C) 1998-2014 Jorgen Ibsen. All Rights Reserved.   //
// (no source code or binaries taken from this site)            //
// http://www.ibsensoftware.com/products_aPLib.html             //
//                                                              //
// Further information:                                         //
// https://github.com/z88dk/z88dk/blob/master/libsrc/_DEVELOPMENT/compress/aplib/readme.txt
//                                                              //
//////////////////////////////////////////////////////////////////

extern void __LIB__ aplib_depack(void *dst,void *src) __smallc;
extern void __LIB__ aplib_depack_callee(void *dst,void *src) __smallc __z88dk_callee;
#define aplib_depack(a,b) aplib_depack_callee(a,b)



#ifdef __SMS
extern void __LIB__ sms_aplib_depack_vram(unsigned int dst,void *src) __smallc;
extern void __LIB__ sms_aplib_depack_vram_callee(unsigned int dst,void *src) __smallc __z88dk_callee;
#define sms_aplib_depack_vram(a,b) sms_aplib_depack_vram_callee(a,b)


#endif

#endif
