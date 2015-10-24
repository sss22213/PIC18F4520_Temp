/* 
 * File:   Temp.h
 * Author: bohome
 *
 * Created on 2015年4月8日, 上午 9:30
 */

#ifndef _Temp
#define	_Temp

//OSC
#define _XTAL_FREQ 4000000

//XC8 Header
#include "htc.h"

//DS18B20 I/O
#define Temp RA4

//Write bit
extern void Write_bit(unsigned char);

//Reset
 extern unsigned char reset(void);

//Read bit
 extern unsigned char Read_bit(void);

//Temp Init
 extern void ConvertT(void);


//Temp1:整數  Temp2:小數
extern void read_T (void);


#endif