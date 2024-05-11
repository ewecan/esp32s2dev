
#include "displayMenu.h"
#include "stdio.h"

/**
 * @brief 欢迎显示界面
 */
void displayMenuSelect_FLAG(void)
{
	TFT_Display_Image_Select(CS1_PIN, pic_systemTheme_LeftEnter);
	// TFT_Display_Image_Select(CS2_PIN, pic_systemTheme_space);
	// TFT_Display_Image_Select(CS5_PIN, pic_systemTheme_space);
	TFT_Display_Image_Select(CS6_PIN, pic_systemTheme_Right);

	TFT_Display_Image_Select(CS4_PIN, pic_systemTheme_SetFLAG);
	TFT_Display_Image_Select(CS3_PIN, pic_systemTheme_FLAG);
}
/**
 * @brief 欢迎界面 按键操作
 * @param  key  按键键码
 */
void displayMenuSelect_FLAG_KEY(int8_t key)
{
	switch (key) //根据按键键值  执行
	{
	case 1: //按键1    右
	{
		Same_Last();
		TFT_Display_Clear(CS2_PIN, CS5_PIN);
	}
	break;
	case 2: //按键2  下
	{
		TFT_Display_Clear(CS1_PIN, CS6_PIN);
		TFT_Display_Image_Select(CS1_PIN, pic_systemTheme_Left);
		TFT_Display_Image_Select(CS2_PIN, pic_systemTheme_FLAG);

		TFT_Display_Image_Select(CS4_PIN, pic_systemTheme_SetFLAG);
		TFT_Display_Image_Select(CS6_PIN, pic_systemTheme_RightBack);

		Enter_Next(3);
	}
	break;
	case 3: //按键3   左
	{
		Same_Next();
		TFT_Display_Clear(CS2_PIN, CS5_PIN);
	}
	break;
	case 4: //按键4 	确认
	{
		// Retern_Up(2);
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
