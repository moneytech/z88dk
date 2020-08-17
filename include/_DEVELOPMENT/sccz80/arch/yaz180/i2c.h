
// automatically generated by m4 from headers in proto subdir


#ifndef __I2C_H__
#define __I2C_H__

#include <stdint.h>
#include <stddef.h>
#include <arch.h>

// Defines

#define I2C1_PORT   __IO_I2C1_PORT_MSB
#define I2C2_PORT   __IO_I2C2_PORT_MSB

#define I2C_CON_ECHO_BUS_STOPPED    __IO_I2C_CON_ECHO_BUS_STOPPED
#define I2C_CON_ECHO_BUS_RESTART    __IO_I2C_CON_ECHO_BUS_RESTART
#define I2C_CON_ECHO_BUS_ILLEGAL    __IO_I2C_CON_ECHO_BUS_ILLEGAL

#define I2C_RESTART_ENABLE          0
#define I2C_RESTART                 I2C_RESTART_ENABLE
#define I2C_RESTART_DISABLE         __IO_I2C_CON_STO
#define I2C_STOP                    I2C_RESTART_DISABLE

#define I2C_MODE_BYTE               0
#define I2C_MODE_BUFFER             __IO_I2C_CON_MODE

#define I2C_RX_SENTENCE             __IO_I2C_RX_SIZE
#define I2C_TX_SENTENCE             __IO_I2C_TX_SIZE

// Data Structures

typedef enum {
    I2C_SPEED_STD           = 0,
    I2C_SPEED_FAST          = 1,
    I2C_SPEED_FAST_PLUS     = 2,
    I2C_SPEED_PLAID         = 3,
} i2c_speed_mode;

// Functions

// Interrupt routines for the I2C interfaces - Bus Master only
extern void i2c1_isr(void);
extern void i2c2_isr(void);

// void i2c_reset( uint8_t device ) __z88dk_fastcall;
extern void __LIB__ i2c_reset(uint8_t device) __smallc __z88dk_fastcall;



// void i2c_initialise( uint8_t device ) __z88dk_fastcall;
extern void __LIB__ i2c_initialise(uint8_t device) __smallc __z88dk_fastcall;



// void i2c_available( uint8_t device ) __z88dk_fastcall;
extern uint8_t __LIB__ i2c_available(uint8_t device) __smallc __z88dk_fastcall;



// void i2c_set_speed( uint8_t device, enum i2c_speed_mode ) __z88dk_callee;
extern void __LIB__ i2c_set_speed(uint8_t device,i2c_speed_mode speed) __smallc;
extern void __LIB__ i2c_set_speed_callee(uint8_t device,i2c_speed_mode speed) __smallc __z88dk_callee;
#define i2c_set_speed(a,b) i2c_set_speed_callee(a,b)



// void i2c_interrupt_attach( uint8_t device, void *isr ) __z88dk_callee;
extern void __LIB__ i2c_interrupt_attach(uint8_t device,void *isr) __smallc;
extern void __LIB__ i2c_interrupt_attach_callee(uint8_t device,void *isr) __smallc __z88dk_callee;
#define i2c_interrupt_attach(a,b) i2c_interrupt_attach_callee(a,b)



// void i2c_write( uint8_t device, uint8_t addr, uint8_t *dp, uint8_t length, uint8_t stop ) __z88dk_callee;
extern void __LIB__ i2c_write(uint8_t device,uint8_t addr,uint8_t *dp,uint8_t length,uint8_t mode) __smallc;
extern void __LIB__ i2c_write_callee(uint8_t device,uint8_t addr,uint8_t *dp,uint8_t length,uint8_t mode) __smallc __z88dk_callee;
#define i2c_write(a,b,c,d,e) i2c_write_callee(a,b,c,d,e)



// void i2c_read_set( uint8_t device, uint8_t addr, uint8_t *dp, uint8_t length, uint8_t stop ) __z88dk_callee;
extern void __LIB__ i2c_read_set(uint8_t device,uint8_t addr,uint8_t *dp,uint8_t length,uint8_t mode) __smallc;
extern void __LIB__ i2c_read_set_callee(uint8_t device,uint8_t addr,uint8_t *dp,uint8_t length,uint8_t mode) __smallc __z88dk_callee;
#define i2c_read_set(a,b,c,d,e) i2c_read_set_callee(a,b,c,d,e)



// uint8_t i2c_read_chk( uint8_t device, uint8_t addr, uint8_t length ) __z88dk_callee;
extern uint8_t __LIB__ i2c_read_chk(uint8_t device,uint8_t addr,uint8_t length) __smallc;
extern uint8_t __LIB__ i2c_read_chk_callee(uint8_t device,uint8_t addr,uint8_t length) __smallc __z88dk_callee;
#define i2c_read_chk(a,b,c) i2c_read_chk_callee(a,b,c)



// uint8_t i2c_read_get( uint8_t device, uint8_t addr, uint8_t length ) __z88dk_callee;
extern uint8_t __LIB__ i2c_read_get(uint8_t device,uint8_t addr,uint8_t length) __smallc;
extern uint8_t __LIB__ i2c_read_get_callee(uint8_t device,uint8_t addr,uint8_t length) __smallc __z88dk_callee;
#define i2c_read_get(a,b,c) i2c_read_get_callee(a,b,c)



#endif
