
#include "stdio.h"
#include "displayMenu.h"

extern MenuItem_t m0_main[1];
extern MenuItem_t m1_main[5];
extern MenuItem_t m2_main[5];

//欢迎界面
void displayMenuWelcome(void);
void displayMenuWelcome_KEY(int8_t key);
//设备配置列表
void displayMenuSelect_CLK(void);
void displayMenuSelect_CLK_KEY(int8_t key);
void displayMenuSelect_BRT(void);
void displayMenuSelect_BRT_KEY(int8_t key);
void displayMenuSelect_PIC(void);
void displayMenuSelect_PIC_KEY(int8_t key);
void displayMenuSelect_FLAG(void);
void displayMenuSelect_FLAG_KEY(int8_t key);
void displayMenuSelect_UPCLK(void);
void displayMenuSelect_UPCLK_KEY(int8_t key);
//功能菜单
void displayMenuFunction_CLK(void);
void displayMenuFunction_CLK_KEY(int8_t key);
void displayMenuFunction_BRT(void);
void displayMenuFunction_BRT_KEY(int8_t key);
void displayMenuFunction_PIC(void);
void displayMenuFunction_PIC_KEY(int8_t key);
void displayMenuFunction_FLAG(void);
void displayMenuFunction_FLAG_KEY(int8_t key);
void displayMenuFunction_UPCLK(void);
void displayMenuFunction_UPCLK_KEY(int8_t key);
//一级菜单  欢迎界面
MenuItem_t m0_main[1] = {
	{1, 1, 0, 0, displayMenuWelcome, displayMenuWelcome_KEY, m2_main, 0}, //欢迎界面
};

//二级菜单 选择设置项
MenuItem_t m1_main[5] = {
	{5, 1, 0, 0, displayMenuSelect_CLK, displayMenuSelect_CLK_KEY, m2_main, m0_main},
	{5, 2, 0, 0, displayMenuSelect_BRT, displayMenuSelect_BRT_KEY, m2_main, m0_main},
	{5, 3, 0, 0, displayMenuSelect_PIC, displayMenuSelect_PIC_KEY, m2_main, m0_main},
	{5, 4, 0, 0, displayMenuSelect_FLAG, displayMenuSelect_FLAG_KEY, m2_main, m0_main},
	{5, 5, 0, 0, displayMenuSelect_UPCLK, displayMenuSelect_UPCLK_KEY, m2_main, m0_main},
};

//三级菜单 设置参数
MenuItem_t m2_main[5] = {
	{5, 1, 0, 0, displayMenuFunction_CLK, displayMenuFunction_CLK_KEY, 0, m1_main},
	{5, 2, 0, 0, displayMenuFunction_BRT, displayMenuFunction_BRT_KEY, 0, m1_main},
	{5, 3, 0, 0, displayMenuFunction_PIC, displayMenuFunction_PIC_KEY, 0, m1_main},
	{5, 4, 0, 0, displayMenuFunction_FLAG, displayMenuFunction_FLAG_KEY, 0, m1_main},
	{5, 5, 0, 0, displayMenuFunction_UPCLK, displayMenuFunction_UPCLK_KEY, 0, m1_main},
};
/*******************************************************************************/
static struct MenuItem *manyou = m0_main; //开始的位置

//执行界面
static void Run(int8_t key) //优化:去除不必要的参数
{
	if (key != 0)
	{
		manyou->Key(key);
	}
	manyou->Subs();
}

//切换到同级下一个界面
void Same_Next(void)
{
	//寻找下一个界面的坐标
	if (manyou->Loc < (manyou->MenuCount)) // 如果不是最后一个界面
	{
		manyou++; //切换到下一个界面
	}
	else
	{
		manyou = (manyou - (manyou->MenuCount - 1)); //切回到第一个
	}
}

//切换到同级上一个界面
void Same_Last(void)
{
	//寻找上一个界面的坐标
	if (manyou->Loc > 1) // 如果不是第一个界面
	{
		manyou--; //切换到上一个界面
	}
	else
	{
		manyou = manyou + (manyou->MenuCount - 1); //切回到最后一个
	}
}
//进入下一级菜单的第几个界面
void Enter_Next(int8_t lev)
{
	if (manyou->Childrenms != NULL) //如果有子菜单
	{
		//进入下一级菜单
		if (lev < manyou->Childrenms->MenuCount)
		{
			manyou->Childrenms->RunLoc = manyou->Loc; //记录上一级时的所在界面
			manyou = (manyou->Childrenms + lev);
		}
	}
}

//返回上一级菜单的第几个界面
void Retern_Up(int8_t lev)
{
	if (manyou->Parentms != 0)
	{
		//返回上一级菜单
		if ((lev < manyou->Parentms->MenuCount) || (lev == 99))
		{
			manyou->Button_Loc = 0; //按键归位
			// manyou=(lev==99)?manyou->Parentms:(manyou->Parentms + lev);
			if (lev == 99)
				manyou = (manyou->Parentms + manyou->RunLoc - 1);
			else
				manyou = (manyou->Parentms + lev);
		}
	}
}

void MenuSwitch(int8_t key) //界面切换  参数设定
{
	Run(key); //执行  指向的界面
}
