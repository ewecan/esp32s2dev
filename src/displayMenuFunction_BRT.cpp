
#include "displayMenu.h"
#include "stdio.h"
#include "Adafruit_NeoPixel.h"
// static int BrtLevel = 1;
/**
 * @brief 欢迎显示界面
 */
extern Adafruit_NeoPixel pixel;
void displayMenuFunction_BRT(void)
{
}
/**
 * @brief 欢迎界面 按键操作
 * @param  key  按键键码
 */
void displayMenuFunction_BRT_KEY(int8_t key)
{
	switch (key) //根据按键键值  执行
	{
	case 1: //按键1
	{
		TFTConfig.BrtLevel--;
		if (TFTConfig.BrtLevel < 1)
		{
			TFTConfig.BrtLevel = 1;
		}
		pixel.setBrightness(25 * (TFTConfig.BrtLevel));
		//青蓝色
		pixel.setPixelColor(0, 0, 255, 255);
		pixel.show();
		TFT_Display_Brightness(pow(2, TFTConfig.BrtLevel));
		TFT_Display_Num(CS3_PIN, TFTConfig.BrtLevel);
	}
	break;
	case 2: //按键2  下
	{
	}
	break;
	case 3: //按键3
	{
		TFTConfig.BrtLevel++;
		if (TFTConfig.BrtLevel > 9)
		{
			TFTConfig.BrtLevel = 9;
		}
		pixel.setBrightness(25 * (TFTConfig.BrtLevel));
		pixel.setPixelColor(0, 0, 255, 255);

		pixel.show();
		TFT_Display_Brightness(pow(2, TFTConfig.BrtLevel));
		TFT_Display_Num(CS3_PIN, TFTConfig.BrtLevel);
	}
	break;
	case 4: //按键4 	确认
	{
		TFT_Display_Clear(CS1_PIN, CS6_PIN);
		// Retern_Up(1);
		Retern_Up(0);
		Enter_Next(0);
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
