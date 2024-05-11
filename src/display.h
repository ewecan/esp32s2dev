#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "Arduino.h"

#include <SPI.h>
#include <TFT_eSPI.h>
#include "main.h"
#include "pic_clock_SEG14.h"
#include "pic_clock_VDF.h"
#include "pic_systemTheme.h"

typedef struct
{
    int theme_index;       //主题索引
    int theme_index2;      //主题索引2

    int theme_dispAnimate; //主题动画索引
    int8_t time_date;      //时间日期
    uint8_t BrtLevel;      //亮度等级
    uint16_t LEDcolor;      //LED颜色
} TFTConfig_t;

void TFT_Display_Init(int PinFirst, int PinLast);
void TFT_Display_Clear(int PinFirst, int PinLast);
void TFT_Display_Brightness(int brightness);
void TFT_Display_Clear_Select(int PinSelect);

void TFT_Display_String(int PinFirst, int PinLast, int x, int y, const char *str, uint16_t color, uint8_t size);
void TFT_Display_String_Select(int PinSelect, int x, int y, const char *str, uint16_t color, uint8_t size);

void TFT_Display_Image(int PinFirst, int PinLast, const uint16_t *data);
void TFT_Display_Image_Select(int PinSelect, const uint16_t *data);


void TFT_Display_Num(int PinSelect, int num);

void TFT_Display_CLK_Num(uint8_t PinSelect, uint8_t num, uint8_t theme);
void TFT_CLK_DispTime(uint8_t hour, uint8_t minute, uint8_t theme);
void TFT_CLK_DispColon(bool clkflag, uint8_t theme, bool time_date);
void TFT_CLK_DispAM_PM(uint8_t hour, uint8_t theme);

void TFT_CLK_DispAnimate(uint8_t index);

extern char LCD_CACHE[50];
extern TFTConfig_t TFTConfig;

#endif
