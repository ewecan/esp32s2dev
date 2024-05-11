
#include "displayMenu.h"
#include "stdio.h"

#include "wifi_ntp.h"
#include "Adafruit_NeoPixel.h"
#include "stdio.h"
#include "stdlib.h"
extern Adafruit_NeoPixel pixel;
/**
 * @brief 欢迎显示界面
 */
void displayMenuFunction_CLK(void)
{
	struct tm time;

	Get_NTP(&time, 500); //获取NTP时间

	LCD_CACHE[0]++;
	if (LCD_CACHE[0] > 5)
	{
		LCD_CACHE[0] = 0;
		LCD_CACHE[1] = !LCD_CACHE[1];
	}

	LCD_CACHE[2]++;
	if (LCD_CACHE[2] > 3)
	{
		LCD_CACHE[2] = 0;
	}
	if (TFTConfig.time_date == 0)
	{
		TFT_CLK_DispColon(LCD_CACHE[1], TFTConfig.theme_index, TFTConfig.time_date); //显示时间
		TFT_CLK_DispTime(time.tm_hour, time.tm_min, TFTConfig.theme_index);
	}
	else
	{
		TFT_CLK_DispColon(LCD_CACHE[1], TFTConfig.theme_index, TFTConfig.time_date); //显示时间
		TFT_CLK_DispTime(time.tm_mon + 1, time.tm_mday, TFTConfig.theme_index);

		// snprintf(LCD_CACHE, 20, "%d", time.tm_yday,time.tm_mday,time.tm_);
		// TFT_Display_String_Select(CS6_PIN, 0, 20, LCD_CACHE, TFT_GREEN, 1); //显示字符串
		// 																	// TFT_CLK_DispDate(time.tm_mday, time.tm_mon, time.tm_year, TFTConfig.theme_index);
	}
	switch (TFTConfig.theme_index2)
	{
	case 0:
		TFT_CLK_DispAM_PM(time.tm_hour, TFTConfig.theme_index);
		break;
	case 1:
		TFT_CLK_DispAnimate(LCD_CACHE[2]);
		break;
	case 2:
		TFT_Display_Image_Select(CS6_PIN, pic_logo);
		break;
	default:
		break;
	}

	// snprintf(LCD_CACHE, 50, "%d:%d", time.tm_hour, time.tm_min);	   //显示时间
	// TFT_Display_String_Select(CS1_PIN, 0, 0, LCD_CACHE, TFT_GREEN, 2); //显示时间
}
/**
 * @brief 欢迎界面 按键操作
 * @param  key  按键键码
 */
void displayMenuFunction_CLK_KEY(int8_t key)
{
	switch (key) //根据按键键值  执行
	{
	case 1: //按键1    右
	{
		TFTConfig.time_date++;
		if (TFTConfig.time_date > 1)
			TFTConfig.time_date = 0;
	}
	break;
	case 2: //按键2  下
	{
		//改变pixel颜色
		// TFTConfig.LEDcolor =500;
		// // pixel.setPixelColor(0, TFTConfig.LEDcolor*2);
		// uint32_t color = pixel.gamma32(pixel.ColorHSV(TFTConfig.LEDcolor));;
		// pixel.setPixelColor(0, color);
		// pixel.show();
		pixel.setPixelColor(0, rand() % 250, rand() % 250, rand() % 250);
		pixel.show();
		// Enter_Next(0);
	}
	break;
	case 3: //按键3   左
	{
		TFTConfig.time_date--;
		if (TFTConfig.time_date < 0)
			TFTConfig.time_date = 1;
	}
	break;
	case 4: //按键4 	确认
	{
		TFT_Display_Clear(CS1_PIN, CS6_PIN);
		Retern_Up(0);
	}
	break;
	case 5: //按键5   上
	{
	}
	break;
	case 6: //按键6    取消
	{
	}
	break;
	}
}
