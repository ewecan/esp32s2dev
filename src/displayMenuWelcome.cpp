
#include "displayMenu.h"
#include "stdio.h"

/**
 * @brief 欢迎显示界面
 */
void displayMenuWelcome(void)
{
	if (LCD_CACHE[0] > 80)
	{
		LCD_CACHE[0] = 0;
		TFT_Display_Clear(CS1_PIN, CS6_PIN);
		Enter_Next(0);
	}
	LCD_CACHE[0]++;
	// TFT_Display_Clear(CS1_PIN, CS2_PIN);
	// TFT_Display_Clear(CS5_PIN, CS6_PIN);
	// TFT_Display_Image_Select(CS3_PIN,pic_systemTheme_H);
	// TFT_Display_Image_Select(CS4_PIN,pic_systemTheme_I);
}

/**
 * @brief 欢迎界面 按键操作
 * @param  key  按键键码
 */
void displayMenuWelcome_KEY(int8_t key)
{
	switch (key)
	{
	case 1: //按键1
	{
	}
	break;
	case 2: //按键2
	{
		Enter_Next(0);
	}
	break;
	case 3: //按键3
	{
	}
	break;
	case 4: //按键4
	{
	}
	break;
	case 5: //按键5
	{
	}
	break;

	case 6: //按键6
	{
	}
	break;
	}
}
