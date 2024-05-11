
#include "displayMenu.h"
#include "stdio.h"
#include "stdlib.h"

/**
 * @brief 欢迎显示界面
 */
void displayMenuFunction_PIC(void)
{
}
/**
 * @brief 欢迎界面 按键操作
 * @param  key  按键键码
 */
void displayMenuFunction_PIC_KEY(int8_t key)
{
	switch (key) //根据按键键值  执行
	{
	case 1: //按键1
	{
		TFTConfig.theme_index++;
		if (TFTConfig.theme_index > 2)
			TFTConfig.theme_index = 0;

		// TFT_Display_CLK_Num(CS2_PIN, rand() % 10, TFTConfig.theme_index);
		TFT_Display_CLK_Num(CS3_PIN, rand() % 10, TFTConfig.theme_index);
		TFT_Display_CLK_Num(CS4_PIN, rand() % 10, TFTConfig.theme_index);
		TFT_Display_CLK_Num(CS5_PIN, rand() % 10, TFTConfig.theme_index);
	}
	break;
	case 2: //按键2  下
	{
		// Enter_Next(0);
	}
	break;
	case 3: //按键3
	{
		TFTConfig.theme_index--;
		if (TFTConfig.theme_index < 0)
			TFTConfig.theme_index = 2;

		// TFT_Display_CLK_Num(CS2_PIN, rand() % 10, TFTConfig.theme_index);
		TFT_Display_CLK_Num(CS3_PIN, rand() % 10, TFTConfig.theme_index);
		TFT_Display_CLK_Num(CS4_PIN, rand() % 10, TFTConfig.theme_index);
		TFT_Display_CLK_Num(CS5_PIN, rand() % 10, TFTConfig.theme_index);
	}
	break;
	case 4: //按键4 	确认
	{
		TFT_Display_Clear(CS1_PIN, CS6_PIN);
		// Retern_Up(2);
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
