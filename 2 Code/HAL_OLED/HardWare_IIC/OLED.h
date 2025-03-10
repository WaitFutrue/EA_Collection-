#ifndef __OLED_H__
#define __OLED_H__


#include <i2c.h>
#include <OLED.h>

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void XY(uint8_t x,uint8_t y);
void X2Y2(uint8_t x,uint8_t y);
void light_init(uint8_t t);
void OLED_ADC(uint16_t ADC_IME[8][128]);
void OLED_ShowfloatNum(uint8_t Line, uint8_t Column, float Number,uint8_t int_Length,uint8_t float_Length);


#endif 
