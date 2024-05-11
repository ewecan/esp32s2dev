#include "key.h"
#include "button.h"

#include "main.h"
#include "FreeRTOS.h"
#include "queue.h"

static QueueHandle_t xQueueKey;
static uint8_t key_num = 0;

static Button key1;
static Button key2;
static Button key3;
static Button key4;

static uint8_t ReadKey1(void)
{
    if (!digitalRead(BUTTON_PIN_1))
        return 1;
    else
        return 0;
}

static uint8_t ReadKey2(void)
{
    if (!digitalRead(BUTTON_PIN_2))
        return 1;
    else
        return 0;
}

static uint8_t ReadKey3(void)
{
    if (!digitalRead(BUTTON_PIN_3))
        return 1;
    else
        return 0;
}

static uint8_t ReadKey4(void)
{
    if (!digitalRead(BUTTON_PIN_4))
        return 1;
    else
        return 0;
}

static void Key1_Handler(void *btn, uint8_t event)
{
    if (event & PRESS_DOWN)
    {
        key_num = 1;
        xQueueSend(xQueueKey,
                   (void *)&key_num,
                   (TickType_t)10);
    }
}

static void Key2_Handler(void *btn, uint8_t event)
{
    if (event & PRESS_DOWN)
    {
        key_num = 2;
        xQueueSend(xQueueKey,
                   (void *)&key_num,
                   (TickType_t)10);
    }
}

static void Key3_Handler(void *btn, uint8_t event)
{
    if (event & PRESS_DOWN)
    {
        key_num = 3;
        xQueueSend(xQueueKey,
                   (void *)&key_num,
                   (TickType_t)10);
    }
}

static void Key4_Handler(void *btn, uint8_t event)
{
    if (event & PRESS_DOWN)
    {
        key_num = 4;
        xQueueSend(xQueueKey,
                   (void *)&key_num,
                   (TickType_t)10);
    }
}

/**
 * @brief 按键初始化,必须放在操作系统任务中
 */
void Key_Init(void)
{
    button_init();

    button_attach(&key1, ReadKey1, Key1_Handler, PRESS_DOWN);
    button_attach(&key2, ReadKey2, Key2_Handler, PRESS_DOWN);
    button_attach(&key3, ReadKey3, Key3_Handler, PRESS_DOWN);
    button_attach(&key4, ReadKey4, Key4_Handler, PRESS_DOWN);

    xQueueKey = xQueueCreate(1, sizeof(uint8_t)); //信号量创建
}

/**
 * @brief 获取按键
 * @param  *ucQueueMsgValue   获取的按键键值
 * @param  xMaxBlockTime    没有按下按键的阻塞时间(操作系统)
 * @return BaseType_t 当前是否有按键按下
 */
long Get_Key(uint8_t *ucQueueMsgValue, uint32_t xMaxBlockTime)
{
    return xQueueReceive(xQueueKey,                  /* 消息队列句柄 */
                         (void *)ucQueueMsgValue,    /* 存储接收到的数据到变量 ucQueueMsgValue 中 */
                         (TickType_t)xMaxBlockTime); /* 设置阻塞时间 */
}
