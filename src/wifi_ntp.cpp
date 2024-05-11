#include "wifi_ntp.h"
#include "wifi_config.h"

#include "main.h"
#include "FreeRTOS.h"
#include "queue.h"
int connectTimeOut_s = 15; // WiFi连接超时时间，单位秒

TimeNTP_t TimeNTP = {.timezone = 8}; //默认时区为北京时间
static QueueHandle_t xQueueNTP;
struct tm timeinfo;

static uint8_t NTPTime = 0;
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

void WIFI_NTP_Init(void)
{
    xQueueNTP = xQueueCreate(1, sizeof(struct tm)); //信号量创建

    connectToWiFi(connectTimeOut_s); //连接WIFI

    // WiFi.mode(WIFI_STA);                            //设置为STA模式

    // delay(500);
    // WiFi.begin(ssid, password);
    TFT_Display_String_Select(CS1_PIN, 0, 140, "OK", TFT_GREEN, 1);          //显示字符串
    TFT_Display_String_Select(CS4_PIN, 0, 0, "Set AP", TFT_GREEN, 2);       //显示字符串
    TFT_Display_String_Select(CS4_PIN, 0, 20, APSSID, TFT_GREEN, 1);        //显示字符串
    TFT_Display_String_Select(CS4_PIN, 0, 40, APIP, TFT_GREEN, 1); //显示字符串
    TFT_Display_String_Select(CS4_PIN, 0, 60, "SetWIFI", TFT_GREEN, 2);          //显示字符串
    TFT_Display_String_Select(CS4_PIN, 0, 80, "SSID   &", TFT_GREEN, 1);      //显示字符串
    TFT_Display_String_Select(CS4_PIN, 0,100, "PASSWORD", TFT_GREEN, 1);      //显示字符串

    while (WiFi.status() != WL_CONNECTED)
    {
        checkDNS_HTTP();    //检测客户端DNS&HTTP请求，也就是检查配网页面那部分
        checkConnect(true); //检测网络连接状态，参数true表示如果断开重新连接
    }

    if (WiFi.status() == WL_CONNECTED)
    {
    }
    else
    {
        // TFT_Display_String_Select(CS4_PIN, 0, 100, "error", TFT_GREEN, 1); //显示字符串
    }

    // TFT_Display_String_Select(CS4_PIN, 0, 40, "ConfigTime", TFT_GREEN, 1); //显示字符串
    configTime(TimeNTP.timezone * 3600, 0, NTP1);
    getLocalTime(&timeinfo);
}

long Get_NTP(struct tm *ucQueueMsgValue, uint32_t xMaxBlockTime)
{
    getLocalTime(&timeinfo);
    xQueueSend(xQueueNTP,
               (void *)&timeinfo,
               (TickType_t)10);

    return xQueueReceive(xQueueNTP,                  /* 消息队列句柄 */
                         (void *)ucQueueMsgValue,    /* 存储接收到的数据到变量 ucQueueMsgValue 中 */
                         (TickType_t)xMaxBlockTime); /* 设置阻塞时间 */
}
