#ifndef __WIFI_NTP_H__
#define __WIFI_NTP_H__

#include <WiFi.h>
#include "display.h"


#define WIFI_SSID "***"
#define WIFI_PASSWORD "***"
#define NTP1 "ntp1.aliyun.com"

typedef struct
{
    int timezone; //时区

} TimeNTP_t;

void WIFI_NTP_Init(void);
void NTPtick(void);
long Get_NTP(struct tm *ucQueueMsgValue, uint32_t xMaxBlockTime);


extern struct tm timeinfo;
extern TimeNTP_t TimeNTP;

#endif //__WIFI_NTP_H__
