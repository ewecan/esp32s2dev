#ifndef __DISPLAYMENU_H__
#define __DISPLAYMENU_H__

#include "display.h"
#include "stdint.h"

//结构体类型定义
struct MenuItem
{
    int8_t MenuCount;  //结构体数组的元素个数
    int8_t Loc;        //每个界面的固定位置
    int8_t RunLoc;     //正在运行的界面
    int8_t Button_Loc; //按键所在位置的键码值

    void (*Subs)();      //执行的函数的指针
    void (*Key)(int8_t); //执行的函数的指针

    struct MenuItem *Childrenms; //指向子节点的指针
    struct MenuItem *Parentms;   //指向父节点的指针
};
typedef struct MenuItem MenuItem_t;


void MenuSwitch(int8_t key); //切换界面
void Enter_Next(int8_t lev);       //进入下一级菜单
void Retern_Up(int8_t lev);        //返回上一级菜单
void Same_Next(void);              //切换到同级下一个界面
void Same_Last(void);              //切换到同级上一个界面

void Retur_Main(void);     //返回主菜单
void Same_Num(int8_t num); //同级任意一界面


#endif //__DISPLAYMENU_H__
