#include "display.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite clk = TFT_eSprite(&tft);
TFTConfig_t TFTConfig = {.theme_index = 1, .BrtLevel = 1};
char LCD_CACHE[50];

//初始化屏幕
void TFT_Display_Init(int PinFirst, int PinLast)
{
    ledcSetup(1, 1, 10);      //设置LEDC通道1频率为1，分辨率为10位，即占空比可选0~1023
    ledcAttachPin(TFT_BL, 1); //将TFT_BL连接到LEDC通道1
#ifdef PIN_SHUN
    for (int i = PinFirst; i <= PinLast; i++)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    tft.init();
    tft.setRotation(4);
    tft.fillScreen(ST7735_BLACK);
    for (int i = PinFirst; i <= PinLast; i++)
    {
        digitalWrite(i, HIGH);
    }
    delay(100);
#else
    for (int i = PinFirst; i >= PinLast; i--)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    tft.init();
    tft.setRotation(4);
    tft.fillScreen(ST7735_BLACK);
    for (int i = PinFirst; i >= PinLast; i--)
    {
        digitalWrite(i, HIGH);
    }
    delay(100);
#endif
}

//设置亮度
void TFT_Display_Brightness(int brightness)
{
    ledcWrite(1, brightness);
}

//清屏
void TFT_Display_Clear(int PinFirst, int PinLast)
{
#ifdef PIN_SHUN
    for (int i = PinFirst; i <= PinLast; i++)
    {
        digitalWrite(i, LOW);
        tft.fillScreen(ST7735_BLACK);
        delay(10);
        digitalWrite(i, HIGH);
    }
#else
    for (int i = PinFirst; i >= PinLast; i--)
    {
        digitalWrite(i, LOW);
        tft.fillScreen(ST7735_BLACK);
        delay(10);
        digitalWrite(i, HIGH);
    }
#endif
}

//选择清屏
void TFT_Display_Clear_Select(int PinSelect)
{

    digitalWrite(PinSelect, LOW);
    tft.fillScreen(ST7735_BLACK);
    delay(10);
    digitalWrite(PinSelect, HIGH);
}

//显示字符串
void TFT_Display_String(int PinFirst, int PinLast, int x, int y, const char *str, uint16_t color, uint8_t size)
{
#ifdef PIN_SHUN
    for (int i = PinFirst; i <= PinLast; i++)
    {
        digitalWrite(i, LOW);

        tft.setTextColor(color);
        tft.setTextSize(size);
        tft.setCursor(x, y);
        tft.print(str);

        digitalWrite(i, HIGH);
    }
#else
    for (int i = PinFirst; i >= PinLast; i--)
    {
        digitalWrite(i, LOW);

        tft.setTextColor(color);
        tft.setTextSize(size);
        tft.setCursor(x, y);
        tft.print(str);

        digitalWrite(i, HIGH);
    }
#endif
}

//选择显示字符串
void TFT_Display_String_Select(int PinSelect, int x, int y, const char *str, uint16_t color, uint8_t size)
{

    digitalWrite(PinSelect, LOW);

    tft.setTextColor(color);
    tft.setTextSize(size);
    tft.setCursor(x, y);
    tft.print(str);

    digitalWrite(PinSelect, HIGH);
}

//显示图片
void TFT_Display_Image(int PinFirst, int PinLast, const uint16_t *data)
{
    tft.setSwapBytes(true);
#ifdef PIN_SHUN
    for (int i = PinFirst; i <= PinLast; i++)
    {
        digitalWrite(i, LOW);

        tft.pushImage(0, 0, 80, 160, data);

        digitalWrite(i, HIGH);
    }
#else
    for (int i = PinFirst; i >= PinLast; i--)
    {
        digitalWrite(i, LOW);

        tft.pushImage(0, 0, 80, 160, data);

        digitalWrite(i, HIGH);
    }
#endif
}

//选择显示图片
void TFT_Display_Image_Select(int PinSelect, const uint16_t *data)
{
    tft.setSwapBytes(true);
    digitalWrite(PinSelect, LOW);
    tft.pushImage(0, 0, 80, 160, data);
    digitalWrite(PinSelect, HIGH);
}
/***************************************************系统显示********************************************************************/
// !
//显示数字
void TFT_Display_Num(int PinSelect, int num)
{
    tft.setSwapBytes(true);
#ifdef PIN_SHUN
    switch (num)
    {
    case 0:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_zero);
        digitalWrite(PinSelect, HIGH);
        break;
    case 1:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_one);
        digitalWrite(PinSelect, HIGH);
        break;
    case 2:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_two);
        digitalWrite(PinSelect, HIGH);
        break;
    case 3:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_three);
        digitalWrite(PinSelect, HIGH);
        break;
    case 4:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_four);
        digitalWrite(PinSelect, HIGH);
        break;
    case 5:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_five);
        digitalWrite(PinSelect, HIGH);
        break;
    case 6:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_six);
        digitalWrite(PinSelect, HIGH);
        break;
    case 7:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_seven);
        digitalWrite(PinSelect, HIGH);
        break;
    case 8:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_eight);
        digitalWrite(PinSelect, HIGH);
        break;
    case 9:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_nine);
        digitalWrite(PinSelect, HIGH);
        break;
    case 10:
        digitalWrite(PinSelect - 1, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_one);
        digitalWrite(PinSelect - 1, HIGH);
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_zero);
        digitalWrite(PinSelect, HIGH);
        break;
    case 11:
        digitalWrite(PinSelect - 1, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_one);
        digitalWrite(PinSelect - 1, HIGH);
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_one);
        digitalWrite(PinSelect, HIGH);
        break;
    case 12:
        digitalWrite(PinSelect - 1, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_one);
        digitalWrite(PinSelect - 1, HIGH);
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_two);
        digitalWrite(PinSelect, HIGH);
        break;
    default:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_space);
        digitalWrite(PinSelect, HIGH);
        break;
    }

#else
    switch (num)
    {
    case 0:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_zero);
        digitalWrite(PinSelect, HIGH);
        break;
    case 1:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_one);
        digitalWrite(PinSelect, HIGH);
        break;
    case 2:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_two);
        digitalWrite(PinSelect, HIGH);
        break;
    case 3:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_three);
        digitalWrite(PinSelect, HIGH);
        break;
    case 4:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_four);
        digitalWrite(PinSelect, HIGH);
        break;
    case 5:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_five);
        digitalWrite(PinSelect, HIGH);
        break;
    case 6:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_six);
        digitalWrite(PinSelect, HIGH);
        break;
    case 7:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_seven);
        digitalWrite(PinSelect, HIGH);
        break;
    case 8:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_eight);
        digitalWrite(PinSelect, HIGH);
        break;
    case 9:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_nine);
        digitalWrite(PinSelect, HIGH);
        break;
    case 10:
        digitalWrite(PinSelect + 1, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_one);
        digitalWrite(PinSelect - 1, HIGH);
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_zero);
        digitalWrite(PinSelect, HIGH);
        break;
    case 11:
        digitalWrite(PinSelect + 1, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_one);
        digitalWrite(PinSelect + 1, HIGH);
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_one);
        digitalWrite(PinSelect, HIGH);
        break;
    case 12:
        digitalWrite(PinSelect + 1, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_one);
        digitalWrite(PinSelect + 1, HIGH);
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_two);
        digitalWrite(PinSelect, HIGH);
        break;
    default:
        digitalWrite(PinSelect, LOW);
        tft.pushImage(0, 0, 80, 160, pic_systemTheme_space);
        digitalWrite(PinSelect, HIGH);
        break;
    }
#endif
}

/***************************************************时间显示********************************************************************/

//显示主题数字
void TFT_Display_CLK_Num(uint8_t PinSelect, uint8_t num, uint8_t theme)
{
    tft.setSwapBytes(true);
    switch (theme)
    {
    case 0:
        switch (num)
        {
        case 0:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_SEG14_zero);
            digitalWrite(PinSelect, HIGH);
            break;
        case 1:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_SEG14_one);
            digitalWrite(PinSelect, HIGH);
            break;
        case 2:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_SEG14_two);
            digitalWrite(PinSelect, HIGH);
            break;
        case 3:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_SEG14_three);
            digitalWrite(PinSelect, HIGH);
            break;
        case 4:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_SEG14_four);
            digitalWrite(PinSelect, HIGH);
            break;
        case 5:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_SEG14_five);
            digitalWrite(PinSelect, HIGH);
            break;
        case 6:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_SEG14_six);
            digitalWrite(PinSelect, HIGH);
            break;
        case 7:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_SEG14_seven);
            digitalWrite(PinSelect, HIGH);
            break;
        case 8:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_SEG14_eight);
            digitalWrite(PinSelect, HIGH);
            break;
        case 9:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_SEG14_nine);
            digitalWrite(PinSelect, HIGH);
            break;
        default:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_SEG14_space);
            digitalWrite(PinSelect, HIGH);
            break;
        }
        break;
    case 1:
        switch (num)
        {
        case 0:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_VDF_zero);
            digitalWrite(PinSelect, HIGH);
            break;
        case 1:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_VDF_one);
            digitalWrite(PinSelect, HIGH);
            break;
        case 2:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_VDF_two);
            digitalWrite(PinSelect, HIGH);
            break;
        case 3:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_VDF_three);
            digitalWrite(PinSelect, HIGH);
            break;
        case 4:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_VDF_four);
            digitalWrite(PinSelect, HIGH);
            break;
        case 5:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_VDF_five);
            digitalWrite(PinSelect, HIGH);
            break;
        case 6:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_VDF_six);
            digitalWrite(PinSelect, HIGH);
            break;
        case 7:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_VDF_seven);
            digitalWrite(PinSelect, HIGH);
            break;
        case 8:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_VDF_eight);
            digitalWrite(PinSelect, HIGH);
            break;
        case 9:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_VDF_nine);
            digitalWrite(PinSelect, HIGH);
            break;
        default:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_clock_VDF_space);
            digitalWrite(PinSelect, HIGH);
            break;
        }
        break;
    case 2:
        switch (num)
        {
        case 0:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_systemTheme_zero);
            digitalWrite(PinSelect, HIGH);
            break;
        case 1:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_systemTheme_one);
            digitalWrite(PinSelect, HIGH);
            break;
        case 2:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_systemTheme_two);
            digitalWrite(PinSelect, HIGH);
            break;
        case 3:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_systemTheme_three);
            digitalWrite(PinSelect, HIGH);
            break;
        case 4:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_systemTheme_four);
            digitalWrite(PinSelect, HIGH);
            break;
        case 5:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_systemTheme_five);
            digitalWrite(PinSelect, HIGH);
            break;
        case 6:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_systemTheme_six);
            digitalWrite(PinSelect, HIGH);
            break;
        case 7:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_systemTheme_seven);
            digitalWrite(PinSelect, HIGH);
            break;
        case 8:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_systemTheme_eight);
            digitalWrite(PinSelect, HIGH);
            break;
        case 9:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_systemTheme_nine);
            digitalWrite(PinSelect, HIGH);
            break;
        default:
            digitalWrite(PinSelect, LOW);
            tft.pushImage(0, 0, 80, 160, pic_systemTheme_space);
            digitalWrite(PinSelect, HIGH);
            break;
        }
        break;
    default:
        break;
    }
}

//显示时间
void TFT_CLK_DispTime(uint8_t hour, uint8_t minute, uint8_t theme)
{
    static uint8_t hour0, hour1, minute0, minute1;

    hour0 = hour / 10;
    hour1 = hour % 10;
    minute0 = minute / 10;
    minute1 = minute % 10;

    TFT_Display_CLK_Num(CS1_PIN, hour0, theme);
    TFT_Display_CLK_Num(CS2_PIN, hour1, theme);
    TFT_Display_CLK_Num(CS4_PIN, minute0, theme);
    TFT_Display_CLK_Num(CS5_PIN, minute1, theme);
}

//显示时间:
void TFT_CLK_DispColon(bool clkflag, uint8_t theme, bool time_date)
{
    if (time_date == 0)
    {
        switch (theme)
        {
        case 0:
            if (clkflag != 0)
                TFT_Display_Image_Select(CS3_PIN, pic_clock_SEG14_colon);
            else
                TFT_Display_Image_Select(CS3_PIN, pic_clock_SEG14_space);
            break;
        case 1:
            if (clkflag != 0)
                TFT_Display_Image_Select(CS3_PIN, pic_clock_VDF_colon);
            else
                TFT_Display_Image_Select(CS3_PIN, pic_clock_VDF_space);
            break;
        case 2:
            if (clkflag != 0)
                TFT_Display_Image_Select(CS3_PIN, pic_systemTheme_colon);
            else
                TFT_Display_Image_Select(CS3_PIN, pic_systemTheme_space);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (theme)
        {
        case 0:
            TFT_Display_Image_Select(CS3_PIN, pic_clock_SEG14_dash);
            break;
        case 1:
            TFT_Display_Image_Select(CS3_PIN, pic_clock_VDF_dash);
            break;
        case 2:
            TFT_Display_Image_Select(CS3_PIN, pic_systemTheme_dash);
            break;
        default:
            break;
        }
    }
}

//显示上午下午
void TFT_CLK_DispAM_PM(uint8_t hour, uint8_t theme)
{
    switch (theme)
    {
    case 0:
        if (hour > 12)
            TFT_Display_Image_Select(CS6_PIN, pic_clock_SEG14_pm);
        else
            TFT_Display_Image_Select(CS6_PIN, pic_clock_SEG14_am);
        break;
    case 1:
        if (hour > 12)
            TFT_Display_Image_Select(CS6_PIN, pic_clock_VDF_pm);

        else
            TFT_Display_Image_Select(CS6_PIN, pic_clock_VDF_am);
        break;
    case 2:
        if (hour > 12)
            TFT_Display_Image_Select(CS6_PIN, pic_systemTheme_pm);
        else
            TFT_Display_Image_Select(CS6_PIN, pic_systemTheme_am);
        break;
    }
}

//显示动画
void TFT_CLK_DispAnimate(uint8_t index)
{
    switch (index)
    {
    case 0:
        TFT_Display_Image_Select(CS6_PIN, pic_cosmonaut1);
        break;
    case 1:
        TFT_Display_Image_Select(CS6_PIN, pic_cosmonaut2);
        break;
    case 2:
        TFT_Display_Image_Select(CS6_PIN, pic_cosmonaut3);
        break;
    case 3:
        TFT_Display_Image_Select(CS6_PIN, pic_cosmonaut4);
        break;
    default:
        break;
    }
}
