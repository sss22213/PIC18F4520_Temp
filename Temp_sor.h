/* 
 * File:   Temp_sor.h
 * Author: bohome
 *
 * Created on 2015年4月9日, 下午 9:46
 */

#ifndef TEMP_SOR_H
#define	TEMP_SOR_H
#define _XTAL_FREQ 4000000
#include "htc.h"
extern unsigned char reset(void);
extern void write_byte(unsigned char);
extern unsigned char read_byte(void);
extern void convert_T(void);
extern void read_T(void);
#endif	/* TEMP_SOR_H */

