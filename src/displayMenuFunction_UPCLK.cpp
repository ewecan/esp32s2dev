
#include "displayMenu.h"
#include "stdio.h"

#include "wifi_ntp.h"

static int timezone;
/**
 * @brief 欢迎显示界面
 */
void displayMenuFunction_UPCLK(void)
{
}
/**
 * @brief 欢迎界面 按键操作
 * @param  key  按键键码
 */
void displayMenuFunction_UPCLK_KEY(int8_t key)
{
	switch (key) //根据按键键值  执行
	{
	case 1: //按键1    左
	{
		TimeNTP.timezone--;
		if (TimeNTP.timezone > 12)
			TimeNTP.timezone = 12;
		else if (TimeNTP.timezone < -12)
			TimeNTP.timezone = -12;
		if (TimeNTP.timezone >= 0 && TimeNTP.timezone <= 9)
		{
			TFT_Display_Image_Select(CS2_PIN, pic_systemTheme_space);
			TFT_Display_Num(CS3_PIN, 0);
			TFT_Display_Num(CS4_PIN, TimeNTP.timezone);
		}
		else if (TimeNTP.timezone > 9 && TimeNTP.timezone <= 12)
		{
			TFT_Display_Image_Select(CS2_PIN, pic_systemTheme_space);
			TFT_Display_Num(CS4_PIN, TimeNTP.timezone);
		}
		else if (TimeNTP.timezone < 0 && TimeNTP.timezone >= -9)
		{
			TFT_Display_Image_Select(CS2_PIN, pic_systemTheme_space);
			TFT_Display_Image_Select(CS3_PIN, pic_systemTheme_dash);
			TFT_Display_Num(CS4_PIN, -TimeNTP.timezone);
		}
		else
		{
			TFT_Display_Image_Select(CS2_PIN, pic_systemTheme_dash);
			TFT_Display_Num(CS4_PIN, -TimeNTP.timezone);
		}
	}
	break;
	case 2: //按键2  下
	{
		// Enter_Next(0);
	}
	break;
	case 3: //按键3   右
	{
		TimeNTP.timezone++;
		if (TimeNTP.timezone > 12)
			TimeNTP.timezone = 12;
		else if (TimeNTP.timezone < -12)
			TimeNTP.timezone = -12;
		if (TimeNTP.timezone >= 0 && TimeNTP.timezone <= 9)
		{
			TFT_Display_Image_Select(CS2_PIN, pic_systemTheme_space);
			TFT_Display_Num(CS3_PIN, 0);
			TFT_Display_Num(CS4_PIN, TimeNTP.timezone);
		}
		else if (TimeNTP.timezone > 9 && TimeNTP.timezone <= 12)
		{
			TFT_Display_Image_Select(CS2_PIN, pic_systemTheme_space);
			TFT_Display_Num(CS4_PIN, TimeNTP.timezone);
		}
		else if (TimeNTP.timezone < 0 && TimeNTP.timezone >= -9)
		{
			TFT_Display_Image_Select(CS2_PIN, pic_systemTheme_space);
			TFT_Display_Image_Select(CS3_PIN, pic_systemTheme_dash);
			TFT_Display_Num(CS4_PIN, -TimeNTP.timezone);
		}
		else
		{
			TFT_Display_Image_Select(CS2_PIN, pic_systemTheme_dash);
			TFT_Display_Num(CS4_PIN, -TimeNTP.timezone);
		}
	}
	break;
	case 4: //按键4 	确认
	{
		TFT_Display_Clear(CS1_PIN, CS6_PIN);
		// Retern_Up(4);
		Retern_Up(0);
		Enter_Next(0);
		configTime(TimeNTP.timezone * 3600, 0, NTP1);
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
