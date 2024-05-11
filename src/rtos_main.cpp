#include "rtos_main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"

/**外设库*/
#include "key.h"
#include "button.h"
#include "display.h"
#include "displayMenu.h"
#include "wifi_ntp.h"
#include "wifi_config.h"
#include "Adafruit_NeoPixel.h"
static QueueHandle_t xQueueKey;
static QueueHandle_t xQueueNTP;
static void vDisplay_Task(void *argument);
// static void vWiFiNTP_Task(void *argument);

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PINSLED, NEO_GRB + NEO_KHZ800);

/**
 * @brief 硬件初始化
 */
void Hart_Init(void)
{

    delay(50);

    TFT_Display_Init(CS1_PIN, CS6_PIN);          //显示初始化
    TFT_Display_Brightness(100);                 //设置亮度
    TFT_Display_Image_Select(CS6_PIN, pic_logo); //显示字符串

    TFT_Display_String_Select(CS1_PIN, 0, 0, "Init ", TFT_GREEN, 2);   //显示字符串
    TFT_Display_String_Select(CS1_PIN, 0, 20, "TFT OK", TFT_GREEN, 1); //显示字符串
    pixel.begin();
    pixel.setBrightness(50);
    pixel.show();
    pixel.setPixelColor(0, 0, 255, 255);
    pixel.show();                                                      // Initialize all pixels to 'off'
    TFT_Display_String_Select(CS1_PIN, 0, 40, "LED ", TFT_GREEN, 1);   //显示字符串
    TFT_Display_String_Select(CS1_PIN, 0, 60, "OK", TFT_GREEN, 1); //显示字符串
}

/**
 * @brief 软件初始化
 */
void Soft_Init(void)
{
    //初始化按键
    TFT_Display_String_Select(CS1_PIN, 0, 80, "Button Init", TFT_GREEN, 1); //显示字符串
    Key_Init();
    TFT_Display_String_Select(CS1_PIN, 0, 100, "OK", TFT_GREEN, 1); //显示字符串

    // WIFI初始化
    TFT_Display_String_Select(CS1_PIN, 0, 120, "WIFI Init", TFT_GREEN, 1); //显示字符串
    WIFI_NTP_Init();

    //创建显示任务
    xTaskCreate(vDisplay_Task,
                "vDisplay_Task",
                1024 * 18,
                NULL,
                2,
                NULL);
    // xTaskCreate(vWiFiNTP_Task,
    //             "vWiFiNTP_Task",
    //             1024 * 4,
    //             NULL,
    //             3,
    //             NULL);
    while (1)
    {
        vTaskDelay(5);
        //初始化按键扫描
        button_ticks();
        pixel.rainbow(0,1);
        checkDNS_HTTP();    //检测客户端DNS&HTTP请求，也就是检查配网页面那部分
        checkConnect(true); //检测网络连接状态，参数true表示如果断开重新连接

    }
}

/**
 * @brief 获取按键键值,显示屏响应
 * @param  argument
 */
static void vDisplay_Task(void *argument)
{
    uint8_t key_num;

    while (1)
    {
        Get_Key(&key_num, 100);

        MenuSwitch(key_num); //执行界面

        key_num = 0;
    }
}
