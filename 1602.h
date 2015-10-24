/* 
 * File:   1602.h
 * Author: bohome
 *
 * Created on 2015年4月7日, 下午 8:45
 */
#ifndef _1602
#define _1602


//OSC 4M
#define _XTAL_FREQ 4000000

//XC8 Header
#include "htc.h"


//LCD_BUS
#define LCD_BUS PORTD

//Enable
#define E RB3

//Read/write
#define RW RB4

//RS
#define RS RB5

/*   LCD_init(void):       Clear_LCD,Set_8_bits */
extern void LCD_init();

/*   write_com(command):   Write command(no using busy_bus)   */
extern void write_com(unsigned char);

/*   write_data(text):      Write data(no using busy_bus)  */
extern void write_data(unsigned char data);

/*   busy_bus(void):       Read busy bus status  */
extern void busy_bus(void);

/*   dispalay(address,text)  */
extern void dispalay(unsigned char x,unsigned char data);

/*   dispalay_string(string,start_address)  */
extern void dispalay_string(char*,unsigned char);

extern void Clean_screen(void);
#endif



