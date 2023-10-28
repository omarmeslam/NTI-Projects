/*
 * LCD_Cfg.h
 *
 * Created: 14/06/2023 15:38:36
 *  Author: OMAR
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define _4_BIT  0
#define _8_BIT  1

/************************** _8_BIT or _4_BIT **********************/
#define LCD_MODE  _4_BIT

/************************** 4 BIT only ***************************/
#define D4  PINB0
#define D5  PINB1
#define D6  PINB2
#define D7  PINB4


#define RS  PINA3

#define E   PINA2

/************************** 8 BIT only ***************************/
#define LCD_PORT  PA

#endif /* LCD_CFG_H_ */