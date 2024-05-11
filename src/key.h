#ifndef __KEY_H__
#define __KEY_H__

#include "stdint.h"
#include "string.h"

void Key_Init(void);                                            //初始化
void button_ticks(void);                                        //按键扫描
long Get_Key(uint8_t *ucQueueMsgValue, uint32_t xMaxBlockTime); //获取按键值

#endif // __KEY_H__
