include(__link__.m4)

#ifndef _SMS_SMSLIB_H
#define _SMS_SMSLIB_H

#include <arch.h>

/* **************************************************
   SMSlib - C programming library for the SMS/GG
   ( part of devkitSMS - github.com/sverx/devkitSMS )
   Synchronized March 29, 2017
   ************************************************** */

#define SMS_MAXSPRITES  __SMSLIB_MAXSPRITES
#define MD_PAD_SUPPORT  __SMSLIB_ENABLE_MDPAD

/** LIBRARY INITIALIZATION */
/** no need to call - this is inserted automatically into all crts */

__OPROTO(`iyl,iyh',`iyl,iyh',void,,SMS_init,void)

/** VDP OPERATIVE MODE HANDLING FUNCTIONS */

__DPROTO(`b,c,iyl,iyh',`b,c,iyl,iyh',void,,SMS_VDPturnOnFeature,unsigned int feature)
__DPROTO(`b,c,iyl,iyh',`b,c,iyl,iyh',void,,SMS_VDPturnOffFeature, unsigned int feature)

// feature can be one of the following:

// group 0
#define VDPFEATURE_EXTRAHEIGHT      __SMSLIB_VDPFEATURE_EXTRAHEIGHT
#define VDPFEATURE_SHIFTSPRITES     __SMSLIB_VDPFEATURE_SHIFTSPRITES
#define VDPFEATURE_HIDEFIRSTCOL     __SMSLIB_VDPFEATURE_HIDEFIRSTCOL
#define VDPFEATURE_LEFTCOLBLANK     __SMSLIB_VDPFEATURE_LEFTCOLBLANK     // a better name
#define VDPFEATURE_LOCKHSCROLL      __SMSLIB_VDPFEATURE_LOCKHSCROLL
#define VDPFEATURE_LOCKVSCROLL      __SMSLIB_VDPFEATURE_LOCKVSCROLL

// group 1
#define VDPFEATURE_ZOOMSPRITES      __SMSLIB_VDPFEATURE_ZOOMSPRITES
#define VDPFEATURE_USETALLSPRITES   __SMSLIB_VDPFEATURE_USETALLSPRITES
#define VDPFEATURE_240LINES         __SMSLIB_VDPFEATURE_240LINES
#define VDPFEATURE_224LINES         __SMSLIB_VDPFEATURE_224LINES
#define VDPFEATURE_FRAMEIRQ         __SMSLIB_VDPFEATURE_FRAMEIRQ
#define VDPFEATURE_SHOWDISPLAY      __SMSLIB_VDPFEATURE_SHOWDISPLAY

// (it's possible to combine (OR) them if they belong to the same group)
// example: VDPFEATURE_ZOOMSPRITES|VDPFEATURE_USETALLSPRITES

/** HANDY MACROS :) */

#define SMS_displayOn()   SMS_VDPturnOnFeature(VDPFEATURE_SHOWDISPLAY)   // turns display on
#define SMS_displayOff()  SMS_VDPturnOffFeature(VDPFEATURE_SHOWDISPLAY)  // turns display off

/** */

__DPROTO(`b,c,d,e,h,l,iyl,iyh',`b,c,d,e,iyl,iyh',void,,SMS_setBGScrollX,unsigned char scrollX)
__DPROTO(`b,c,d,e,h,l,iyl,iyh',`b,c,d,e,iyl,iyh',void,,SMS_setBGScrollY,unsigned char scrollY)
__DPROTO(`b,c,d,e,h,l,iyl,iyh',`b,c,d,e,iyl,iyh',void,,SMS_setBackdropColor,unsigned char entry)
__DPROTO(`b,c,d,e,h,l,iyl,iyh',`b,c,d,e,iyl,iyh',void,,SMS_useFirstHalfTilesforSprites,unsigned char usefirsthalf)
__DPROTO(`b,iyl,iyh',`b,iyl,iyh',void,,SMS_setSpriteMode,unsigned char mode)

// modes for SMS_setSpriteMode

#define SPRITEMODE_NORMAL         __SMSLIB_SPRITEMODE_NORMAL
#define SPRITEMODE_TALL           __SMSLIB_SPRITEMODE_TALL
#define SPRITEMODE_ZOOMED         __SMSLIB_SPRITEMODE_ZOOMED
#define SPRITEMODE_TALL_ZOOMED    __SMSLIB_SPRITEMODE_TALL_ZOOMED

/** MACRO FOR ROM BANKSWITCHING */

extern volatile unsigned char MM_FFFF;

#define ROM_bank_to_be_mapped_on_slot2   MM_FFFF
#define SMS_mapROMBank(n)                (MM_FFFF=(n))

/** MACRO FOR SRAM ACCESS */

extern volatile unsigned char MM_FFFC;

#define SRAM_bank_to_be_mapped_on_slot2  MM_FFFC
#define SMS_enableSRAM()                 (MM_FFFC=0x08)
#define SMS_enableSRAMBank(n)            (MM_FFFC=((((n)<<2)|0x08)&0x0C))
#define SMS_disableSRAM()                (MM_FFFC=0x00)

// SRAM access is as easy as accessing an array of char

extern unsigned char _SMSlib_SRAM[];
#define SMS_SRAM  _SMSlib_SRAM

/** WAIT UNTIL NEXT VBLANK STARTS */

__OPROTO(`b,c,d,e,iyl,iyh',`b,c,d,e,iyl,iyh',void,,SMS_waitForVBlank,void)

/** FUNCTIONS TO LOAD TILES INTO VRAM */

__DPROTO(`iyl,iyh',`iyl,iyh',void,,SMS_loadTiles,void *src,unsigned int tileFrom, unsigned int size)
__DPROTO(`iyl,iyh',`iyl,iyh',void,,SMS_loadPSGaidencompressedTiles,void *src,unsigned int tilefrom)

/** FUNCTIONS FOR THE TILEMAP */

__DPROTO(`iyl,iyh',`iyl,iyh',void,,SMS_loadTileMap,unsigned char x,unsigned char y,void *src,unsigned int size)
__OPROTO(`iyl,iyh',`iyl,iyh',void,,SMS_loadSTMcompressedTileMapArea,unsigned char x,unsigned char y,void *src,unsigned char width)
__DPROTO(`iyl,iyh',`iyl,iyh',void,,SMS_loadTileMapArea,unsigned char x,unsigned char y,void *src,unsigned char width,unsigned char height)

// turning SMS_loadSTMcompressedTileMap into a define
// void SMS_loadSTMcompressedTileMap (unsigned char x, unsigned char y, unsigned char *src);

#define SMS_loadSTMcompressedTileMap(x,y,src) SMS_loadSTMcompressedTileMapArea(x,y,src,32)

/** RESTARTS - FASTCALL ONLY */

#ifdef __CLANG

extern void SMS_crt0_RST08(unsigned int addr);
extern void _RST08_SMS_crt0_RST08(unsigned int addr);

extern void SMS_crt0_RST18(unsigned int addr);
extern void _RST18_SMS_crt0_RST18(unsigned int addr);

#else

extern void SMS_crt0_RST08(unsigned int addr) __preserves_regs(a,b,d,e,h,l,iyl,iyh) __z88dk_fastcall;
extern void _RST08_SMS_crt0_RST08(unsigned int addr) __preserves_regs(a,b,d,e,h,l,iyl,iyh) __z88dk_fastcall;

extern void SMS_crt0_RST18(unsigned int addr) __preserves_regs(b,c,d,e,h,l,iyl,iyh) __z88dk_fastcall;
extern void _RST18_SMS_crt0_RST18(unsigned int addr) __preserves_regs(b,c,d,e,h,l,iyl,iyh) __z88dk_fastcall;

#endif

#if __SMSLIB_ISRST_SMSCRT0RST08
   #define SMS_crt0_RST08  _RST08_SMS_crt0_RST08
#endif

#if __SMSLIB_ISRST_SMSCRT0RST18
   #define SMS_crt0_RST18  _RST18_SMS_crt0_RST18
#endif

// functions for setting tiles / moving 'cursor'

#define SMS_setTile(tile)  SMS_crt0_RST18(tile)
#define SMS_setAddr(addr)  SMS_crt0_RST08(addr)

/** PNT DEFINE (HAS ADDRESS AND VDP FLAGS) */

#define SMS_PNTAddress  __SMSLIB_PNTADDRESS

// macros for turning x,y into VRAM address

#define XYtoADDR(x,y)             (SMS_PNTAddress|((unsigned int)(y)<<6)|((unsigned char)(x)<<1))
#define SMS_setNextTileatXY(x,y)  SMS_setAddr(XYtoADDR((x),(y)))
#define SMS_setNextTileatLoc(loc) SMS_setAddr(SMS_PNTAddress|((unsigned int)(loc)<<1))
#define SMS_setNextTileatAddr(a)  SMS_setAddr(a)
#define SMS_setTileatXY(x,y,tile) {SMS_setAddr(XYtoADDR((x),(y)));SMS_setTile(tile);}

// handy defines for tilemaps entry

#define TILE_FLIPPED_X            __SMSLIB_TILE_FLIPPED_X
#define TILE_FLIPPED_Y            __SMSLIB_TILE_FLIPPED_Y
#define TILE_USE_SPRITE_PALETTE   __SMSLIB_TILE_USE_SPRITE_PALETTE
#define TILE_PRIORITY             __SMSLIB_TILE_PRIORITY

/** FUNCTIONS FOR SPRITE HANDLING */

__OPROTO(`b,c,d,e,h,l,iyl,iyh',`b,c,d,e,h,l,iyl,iyh',void,,SMS_initSprites,void)
// returns -1 if no more sprites are available
__DPROTO(`iyl,iyh',`iyl,iyh',signed char,,SMS_addSprite,unsigned char x,unsigned char y,unsigned char tile)
__OPROTO(`b,c,iyl,iyh',`b,c,iyl,iyh',signed char,,SMS_reserveSprite,void)
__DPROTO(`b,iyl,iyh',`b,iyl,iyh',void,,SMS_updateSpritePosition,unsigned char sprite,unsigned char x,unsigned char y)
__DPROTO(`b,c,iyl,iyh',`b,c,iyl,iyh',void,,SMS_updateSpriteImage,unsigned char sprite,unsigned char image)
__DPROTO(`a,b,c,iyl,iyh',`b,c,iyl,iyh',void,,SMS_hideSprite,unsigned char sprite)
__DPROTO(`a,b,c,iyl,iyh',`b,c,iyl,iyh',void,,SMS_setClippingWindow,unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1)
// returns -1 if no more sprites are available or sprite clipped
__DPROTO(`iyl,iyh',`iyl,iyh',signed char,,SMS_addSpriteClipping,int x,int y, unsigned char tile)
__OPROTO(`b,c,d,e,iyl,iyh',`b,c,d,e,iyl,iyh',void,,SMS_finalizeSprites,void)
__OPROTO(`d,e,iyl,iyh',`d,e,iyl,iyh',void,,SMS_copySpritestoSAT,void)

/** COLORS / PALETTE HANDLING */

// SMS_CRAMAddress define (has address and VDP flags)

#define SMS_CRAMAddress  __SMSLIB_CRAMADDRESS

// SMS functions to set a color / load palette

__DPROTO(`d,e,iyl,iyh',`d,e,iyl,iyh',void,,SMS_setBGPaletteColor,unsigned char entry,unsigned char color)
__DPROTO(`d,e,iyl,iyh',`d,e,iyl,iyh',void,,SMS_setSpritePaletteColor,unsigned char entry,unsigned char color)
__DPROTO(`d,e,iyl,iyh',`d,e,iyl,iyh',void,,SMS_loadBGPalette,void *palette)
__DPROTO(`d,e,iyl,iyh',`d,e,iyl,iyh',void,,SMS_loadSpritePalette,void *palette)

#define SMS_setNextBGColoratIndex(i)       SMS_setAddr(SMS_CRAMAddress|(i))
#define SMS_setNextSpriteColoratIndex(i)   SMS_setAddr(SMS_CRAMAddress|0x10|(i))

__DPROTO(`b,c,d,e,h,l,iyl,iyh',`b,c,d,e,iyl,iyh',void,,SMS_setColor,unsigned char color)

// SMS macros for colors

#define RGB(r,g,b)        ((r)|((g)<<2)|((b)<<4))
#define RGB8(r,g,b)       (((r)>>6)|(((g)>>6)<<2)|(((b)>>6)<<4))
#define RGBHTML(RGB24bit) (((RGB24bit)>>22)|((((RGB24bit)&0xFFFF)>>14)<<2)|((((RGB24bit)&0xFF)>>6)<<4))

__DPROTO(`c,d,e,iyl,iyh',`c,d,e,iyl,iyh',void,,SMS_loadBGPaletteHalfBrightness,void *palette)
__DPROTO(`c,d,e,iyl,iyh',`c,d,e,iyl,iyh',void,,SMS_loadSpritePaletteHalfBrightness,void *palette)
__OPROTO(`c,d,e,h,l,iyl,iyh',`c,d,e,h,l,iyl,iyh',void,,SMS_zeroBGPalette,void)
__OPROTO(`c,d,e,h,l,iyl,iyh',`c,d,e,h,l,iyl,iyh',void,,SMS_zeroSpritePalette,void)

/** FUNCTIONS TO READ JOYSTICKS */

__OPROTO(`a,b,c,d,e,iyl,iyh',`a,b,c,d,e,iyl,iyh',unsigned int,,SMS_getKeysStatus,void)
__OPROTO(`b,c,d,e,iyl,iyh',`b,c,d,e,iyl,iyh',unsigned int,,SMS_getKeysPressed,void)
__OPROTO(`b,c,d,e,iyl,iyh',`b,c,d,e,iyl,iyh',unsigned int,,SMS_getKeysHeld,void)
__OPROTO(`b,c,d,e,iyl,iyh',`b,c,d,e,iyl,iyh',unsigned int,,SMS_getKeysReleased,void)

// handy defines for joypad handling

#ifndef CONTROLLER_PORTS
#define CONTROLLER_PORTS

#define PORT_A_KEY_UP           __SMSLIB_PORT_A_KEY_UP
#define PORT_A_KEY_DOWN         __SMSLIB_PORT_A_KEY_DOWN
#define PORT_A_KEY_LEFT         __SMSLIB_PORT_A_KEY_LEFT
#define PORT_A_KEY_RIGHT        __SMSLIB_PORT_A_KEY_RIGHT
#define PORT_A_KEY_1            __SMSLIB_PORT_A_KEY_1
#define PORT_A_KEY_2            __SMSLIB_PORT_A_KEY_2
#define PORT_A_KEY_START        __SMSLIB_PORT_A_KEY_START   // handy alias

#define PORT_B_KEY_UP           __SMSLIB_PORT_B_KEY_UP
#define PORT_B_KEY_DOWN         __SMSLIB_PORT_B_KEY_DOWN
#define PORT_B_KEY_LEFT         __SMSLIB_PORT_B_KEY_LEFT
#define PORT_B_KEY_RIGHT        __SMSLIB_PORT_B_KEY_RIGHT
#define PORT_B_KEY_1            __SMSLIB_PORT_B_KEY_1
#define PORT_B_KEY_2            __SMSLIB_PORT_B_KEY_2
#define PORT_B_KEY_START        __SMSLIB_PORT_B_KEY_START   // handy alias

#define RESET_KEY               __SMSLIB_RESET_KEY          // (absent on SMS II)
#define CARTRIDGE_SLOT          __SMSLIB_CARTRIDGE_SLOT     // ???
#define PORT_A_TH               __SMSLIB_PORT_A_TH          // for light gun
#define PORT_B_TH               __SMSLIB_PORT_B_TH          // for light gun

#endif

#if MD_PAD_SUPPORT

// functions to read additional MD buttons

__OPROTO(`a,b,c,d,e,iyl,iyh',`a,b,c,d,e,iyl,iyh',unsigned int,,SMS_getMDKeysStatus,void)
__OPROTO(`b,c,d,e,iyl,iyh',`b,c,d,e,iyl,iyh',unsigned int,,SMS_getMDKeysPressed,void)
__OPROTO(`b,c,d,e,iyl,iyh',`b,c,d,e,iyl,iyh',unsigned int,,SMS_getMDKeysHeld,void)
__OPROTO(`b,c,d,e,iyl,iyh',`b,c,d,e,iyl,iyh',unsigned int,,SMS_getMDKeysReleased,void)

// handy defines for additional MD joypad handling

#define PORT_A_MD_KEY_Z         __SMSLIB_PORT_A_MD_KEY_Z
#define PORT_A_MD_KEY_Y         __SMSLIB_PORT_A_MD_KEY_Y
#define PORT_A_MD_KEY_X         __SMSLIB_PORT_A_MD_KEY_X
#define PORT_A_MD_KEY_MODE      __SMSLIB_PORT_A_MD_KEY_MODE
#define PORT_A_MD_KEY_A         __SMSLIB_PORT_A_MD_KEY_A
#define PORT_A_MD_KEY_START     __SMSLIB_PORT_A_MD_KEY_START

// port B is still missing

#endif

/** SMS - PAUSE HANDLING */

__OPROTO(`a,b,c,d,e,iyl,iyh',`a,b,c,d,e,iyl,iyh',unsigned char,,SMS_queryPauseRequested,void)
__OPROTO(`b,c,d,e,h,l,iyl,iyh',`b,c,d,e,h,l,iyl,iyh',void,,SMS_resetPauseRequest,void)

/** SMS - VDPType HANDLING */

__OPROTO(`a,b,c,d,e,iyl,iyh',`a,b,c,d,e,iyl,iyh',unsigned char,,SMS_VDPType,void)

// WARNING: these constants may change value later, please use defines

#define VDP_PAL   __SMSLIB_VDP_PAL
#define VDP_NTSC  __SMSLIB_VDP_NTSC

/** VDP FLAGS*/

extern volatile unsigned char _SMSlib_VDPFlags;
#define SMS_VDPFlags _SMSlib_VDPFlags

#define VDPFLAG_SPRITEOVERFLOW  __SMSLIB_VDPFLAG_SPRITEOVERFLOW
#define VDPFLAG_SPRITECOLLISION __SMSLIB_VDPFLAG_SPRITECOLLISION

/** LINE INTERRUPT */

__DPROTO(`a,b,c,d,e,h,l,iyl,iyh',`b,c,d,e,iyl,iyh',void,,SMS_setLineInterruptHandler,void *theHandlerFunction)
__DPROTO(`b,c,d,e,h,l,iyl,iyh',`b,c,d,e,iyl,iyh',void,,SMS_setLineCounter,unsigned char count)

#define SMS_enableLineInterrupt()   SMS_VDPturnOnFeature(0x0010)   // turns on line IRQ
#define SMS_disableLineInterrupt()  SMS_VDPturnOffFeature(0x0010)  // turns off line IRQ

/** VCOUNT / HCOUNT */

__OPROTO(`b,c,d,e,h,iyl,iyh',`b,c,d,e,h,iyl,iyh',unsigned char,,SMS_getVCount,void)
__OPROTO(`b,c,d,e,h,iyl,iyh',`b,c,d,e,h,iyl,iyh',unsigned char,,SMS_getHCount,void)

/** LOW LEVEL FUNCTIONS */

__DPROTO(`iyl,iyh',`iyl,iyh',void,,SMS_VRAMmemcpy,unsigned int dst,void *src,unsigned int size)
__DPROTO(`iyl,iyh',`iyl,iyh',void,,SMS_VRAMmemcpy_brief,unsigned int dst,void *src,unsigned char size)
__DPROTO(`iyl,iyh',`iyl,iyh',void,,SMS_VRAMmemset,unsigned int dst,unsigned char value,unsigned int size)
__DPROTO(`iyl,iyh',`iyl,iyh',void,,SMS_VRAMmemsetW,unsigned int dst,unsigned int value,unsigned int size)

/** VRAM UNSAFE FUNCTIONS. FAST BUT DANGEROUS! */

__OPROTO(`a,d,e,iyl,iyh',`a,d,e,iyl,iyh',void,,UNSAFE_SMS_copySpritestoSAT,void)
__DPROTO(`iyl,iyh',`iyl,iyh',void,,UNSAFE_SMS_VRAMmemcpy32,unsigned int dst,void *src)
__DPROTO(`iyl,iyh',`iyl,iyh',void,,UNSAFE_SMS_VRAMmemcpy64,unsigned int dst,void *src)
__DPROTO(`iyl,iyh',`iyl,iyh',void,,UNSAFE_SMS_VRAMmemcpy128,unsigned int dst,void *src)

// handy functions for UNSAFE_SMS_VRAMmemcpy

#define UNSAFE_SMS_load1Tile(src,theTile)     UNSAFE_SMS_VRAMmemcpy32((theTile)*32,(src))
#define UNSAFE_SMS_load2Tiles(src,tilefrom)   UNSAFE_SMS_VRAMmemcpy64((tilefrom)*32,(src))
#define UNSAFE_SMS_load4Tiles(src,tilefrom)   UNSAFE_SMS_VRAMmemcpy128((tilefrom)*32,(src))

/** MACROS FOR SEGA AND SDSC HEADERS */

// headers are automatically generated by z88dk via pragmas
// for compatibility these macros are turned into NOPs

#define SMS_BYTE_TO_BCD(n) (((n)/10)*16+((n)%10))

#define SMS_EMBED_SEGA_ROM_HEADER_REGION_CODE 0x4C

#define SMS_EMBED_SEGA_ROM_HEADER(productCode,revision) 
#define SMS_EMBED_SDSC_HEADER(verMaj,verMin,dateYear,dateMonth,dateDay,author,name,descr) 
#define SMS_EMBED_SDSC_HEADER_AUTO_DATE(verMaj,verMin,author,name,descr) 

/** INTERRUPT SERVICE ROUTINES */

__OPROTO(`a,b,c,d,e,h,l,iyl,iyh',`a,b,c,d,e,h,l,iyl,iyh',void,,SMS_isr,void)
__OPROTO(`a,b,c,d,e,h,l,iyl,iyh',`a,b,c,d,e,h,l,iyl,iyh',void,,SMS_nmi_isr,void)

/** STILL MISSING

void SMS_VDPSetSATLocation (unsigned int location);
void SMS_VDPSetPNTLocation (unsigned int location);
void SMS_VDPSetSpritesLocation (unsigned int location);

In z88dk these constants can be set in the devkitSMS configuration file:
  z88dk/libsrc/_DEVELOPMENT/target/sms/config_devkitSMS.m4

After changes are made the sms library must be rebuilt from directory:
  z88dk/libsrc/_DEVELOPMENT

By running:
  Winmake sms     (windows)
  make TARGET=sms (everything else)

*/

#endif
