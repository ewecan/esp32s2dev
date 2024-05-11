#include "wifi_config.h"

const byte DNS_PORT = 53; //设置DNS端口号
const int webPort = 80;   //设置Web端口号

const char *AP_SSID = APSSID; //设置AP热点名称
// const char* AP_PASS  = "";               //这里不设置设置AP热点密码

const char *HOST_NAME = "MY_ESP32"; //设置设备名
String scanNetworksID = "";         //用于储存扫描到的WiFi ID

IPAddress apIP(192, 168, 4, 1); //设置AP的IP地址

String wifi_ssid = ""; //暂时存储wifi账号密码
String wifi_pass = ""; //暂时存储wifi账号密码

DNSServer dnsServer;       //创建dnsServer实例
WebServer server(webPort); //开启web服务, 创建TCP SERVER,参数: 端口号,最大连接数

#define ROOT_HTML "<!DOCTYPE html><html><head><title>WIFI</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head><style type=\"text/css\">.input{display: block; margin-top: 10px;}.input span{width: 100px; float: left; float: left; height: 36px; line-height: 36px;}.input input{height: 30px;width: 200px;}.btn{width: 120px; height: 35px; background-color: #000000; border:0px; color:#ffffff; margin-top:15px; margin-left:100px;}</style><body><form method=\"POST\" action=\"configwifi\"><label class=\"input\"><span>WiFi SSID</span><input type=\"text\" name=\"ssid\" value=\"\"></label><label class=\"input\"><span>WiFi PASS</span> <input type=\"text\"  name=\"pass\"></label><input class=\"btn\" type=\"submit\" name=\"submit\" value=\"Submie\"> <p><span> Nearby wifi:</P></form>"

/* 处理网站根目录的访问请求*/
void handleRoot()
{
    if (server.hasArg("selectSSID"))
    {
        server.send(200, "text/html", ROOT_HTML + scanNetworksID + "</body></html>"); // scanNetWprksID是扫描到的wifi
    }
    else
    {
        server.send(200, "text/html", ROOT_HTML + scanNetworksID + "</body></html>");
    }
}

/* 提交数据后的提示页面*/
void handleConfigWifi() //返回http状态
{
    TFT_Display_Clear_Select(CS5_PIN); //清屏
    if (server.hasArg("ssid"))         //判断是否有账号参数
    {
        wifi_ssid = server.arg("ssid");                                 //获取html表单输入框name名为"ssid"的内容
        TFT_Display_String_Select(CS5_PIN, 0, 0, "SSID", TFT_GREEN, 2); //显示字符串
        snprintf(LCD_CACHE, 20, "%S", wifi_ssid);
        TFT_Display_String_Select(CS5_PIN, 0, 20, LCD_CACHE, TFT_GREEN, 1); //显示字符串

        // Serial.print("got ssid:");
        // Serial.println(wifi_ssid);
    }
    else //没有参数
    {
        // Serial.println("error, not found ssid");
        TFT_Display_String_Select(CS2_PIN, 0, 20, "ERROR", TFT_GREEN, 1);             //显示字符串
        server.send(200, "text/html", "<meta charset='UTF-8'>error, not found ssid"); //返回错误页面
        return;
    }
    //密码与账号同理
    if (server.hasArg("pass"))
    {
        wifi_pass = server.arg("pass"); //获取html表单输入框name名为"pwd"的内容

        TFT_Display_String_Select(CS5_PIN, 0, 50, "PSWD", TFT_GREEN, 2); //显示字符串
        snprintf(LCD_CACHE, 20, "%S", wifi_pass);
        TFT_Display_String_Select(CS5_PIN, 0, 70, LCD_CACHE, TFT_GREEN, 1); //显示字符串

        // Serial.print("got password:");
        // Serial.println(wifi_pass);
    }
    else
    {
        // Serial.println("error, not found password");
        server.send(200, "text/html", "<meta charset='UTF-8'>error, not found password");
        return;
    }
    server.send(200, "text/html", "<meta charset='UTF-8'>SSID:" + wifi_ssid + "<br />password:" + wifi_pass + "<br />已取得WiFi信息,正在尝试连接,请手动关闭此页面。"); //返回保存成功页面
    delay(2000);
    WiFi.softAPdisconnect(true); //参数设置为true，设备将直接关闭接入点模式，即关闭设备所建立的WiFi网络。
    server.close();              //关闭web服务
    WiFi.softAPdisconnect();     //在不输入参数的情况下调用该函数,将关闭接入点模式,并将当前配置的AP热点网络名和密码设置为空值.
    // Serial.println("WiFi Connect SSID:" + wifi_ssid + "  PASS:" + wifi_pass);

    if (WiFi.status() != WL_CONNECTED) // wifi没有连接成功
    {
        // Serial.println("开始调用连接函数connectToWiFi()..");
        TFT_Display_String_Select(CS5_PIN, 0, 120, "Wait", TFT_GREEN, 2); //显示字符串
        TFT_Display_String_Select(CS5_PIN, 0, 140, "Connect", TFT_GREEN, 1);  //显示字符串
        connectToWiFi(connectTimeOut_s);                                        //重新连接wifi
        TFT_Display_Clear_Select(CS5_PIN);                                      //清屏
    }
    else
    {
        // Serial.println("提交的配置信息自动连接成功..");
    }
}

/* 处理404情况的函数'handleNotFound' */
void handleNotFound() // 当浏览器请求的网络资源无法在服务器找到时通过此自定义函数处理
{
    handleRoot(); //访问不存在目录则返回配置页面
                  //   server.send(404, "text/plain", "404: Not found");
}

/** 进入AP模式*/
void initSoftAP()
{
    WiFi.mode(WIFI_AP);                                         //配置为AP模式
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); //设置AP热点IP和子网掩码
    if (WiFi.softAP(AP_SSID))                                   //开启AP热点,如需要密码则添加第二个参数
    {
        //打印相关信息
        // Serial.println("ESP-32S SoftAP is right.");
        // Serial.print("Soft-AP IP address = ");
        // Serial.println(WiFi.softAPIP());                                            //接入点ip
        // Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str()); //接入点mac

        TFT_Display_String_Select(CS2_PIN, 0, 20, "SetAP IP", TFT_GREEN, 1); //显示字符串
        // snprintf(LCD_CACHE, 20, "%s", WiFi.softAPIP().toString().c_str());
        // TFT_Display_String_Select(CS2_PIN, 0, 20, LCD_CACHE, TFT_GREEN, 1); //显示字符串
    }
    else //开启AP热点失败
    {
        TFT_Display_String_Select(CS2_PIN, 0, 20, "Error", TFT_GREEN, 1); //显示字符串
        // Serial.println("WiFiAP Failed");
        delay(1000);
        // Serial.println("restart now...");
        ESP.restart(); //重启复位esp32
    }
}

/** 开启DNS服务器*/
void initDNS()
{
    TFT_Display_String_Select(CS2_PIN, 0, 40, "DNS", TFT_GREEN, 1); //显示字符串

    if (dnsServer.start(DNS_PORT, "*", apIP)) //判断将所有地址映射到esp32的ip上是否成功
    {
        // Serial.println("start dnsserver success.");
        TFT_Display_String_Select(CS2_PIN, 0, 60, "OK", TFT_GREEN, 1); //显示字符串
    }
    else
    {
        // Serial.println("start dnsserver failed.");
        TFT_Display_String_Select(CS2_PIN, 0, 60, " Error", TFT_GREEN, 1); //显示字符串
    }
}

/* * 初始化WebServer */
void initWebServer()
{
    if (MDNS.begin("esp32")) //给设备设定域名esp32,完整的域名是esp32.local
    {
        // Serial.println("MDNS responder started");
    }
    //必须添加第二个参数HTTP_GET，以下面这种格式去写，否则无法强制门户
    server.on("/", HTTP_GET, handleRoot);                                    //  当浏览器请求服务器根目录(网站首页)时调用自定义函数handleRoot处理，设置主页回调函数，必须添加第二个参数HTTP_GET，否则无法强制门户
    server.on("/configwifi", HTTP_POST, handleConfigWifi);                   //  当浏览器请求服务器/configwifi(表单字段)目录时调用自定义函数handleConfigWifi处理
    server.onNotFound(handleNotFound);                                       //当浏览器请求的网络资源无法在服务器找到时调用自定义函数handleNotFound处理
    server.begin();                                                          //启动TCP SERVER
    TFT_Display_String_Select(CS2_PIN, 0, 80, "WebServer", TFT_GREEN, 1); //显示字符串

    // Serial.println("WebServer started!");
}

/** 扫描附近的WiFi，为了显示在配网界面*/
bool scanWiFi()
{
    // Serial.println("scan start");
    // Serial.println("--------->");

    TFT_Display_String_Select(CS3_PIN, 0, 0, "WiFi", TFT_GREEN, 2); //显示字符串

    // 扫描附近WiFi
    int n = WiFi.scanNetworks();
    // Serial.println("scan done");
    if (n == 0)
    {
        // Serial.println("no networks found");
        TFT_Display_String_Select(CS3_PIN, 0, 20, "No WiFi", TFT_GREEN, 1); //显示字符串
        scanNetworksID = "no networks found";
        return false;
    }
    else
    {
        // Serial.print(n);
        // Serial.println(" networks found");
        for (int i = 0; i < n; ++i)
        {
            // Print SSID and RSSI for each network found
            // Serial.print(i + 1);
            // Serial.print(": ");
            // Serial.print(WiFi.SSID(i));
            // Serial.print(" (");
            // Serial.print(WiFi.RSSI(i));
            // Serial.print(")");
            // Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");

            // snprintf(LCD_CACHE, 20, "%S", WiFi.SSID(i));
            // TFT_Display_String_Select(CS3_PIN, 0, 20 + i * 20, LCD_CACHE, TFT_GREEN, 1); //显示字符串
            TFT_Display_String_Select(CS3_PIN, 0, 20, "Search WiFi", TFT_GREEN, 1); //显示字符串
            TFT_Display_String_Select(CS3_PIN, 0, 40, "Waiting", TFT_GREEN, 1); //显示字符串

            scanNetworksID += "<P>" + WiFi.SSID(i) + "</P>";
            delay(10);
        }
        return true;
    }
}

/** 连接WiFi*/
void connectToWiFi(int timeOut_s)
{
    WiFi.hostname(HOST_NAME);  //设置设备名
    WiFi.mode(WIFI_STA);       //设置为STA模式并连接WIFI
    WiFi.setAutoConnect(true); //设置自动连接

    if (wifi_ssid != "") // wifi_ssid不为空，意味着从网页读取到wifi
    {
        // Serial.println("用web配置信息连接.");
        WiFi.begin(wifi_ssid.c_str(), wifi_pass.c_str()); // c_str(),获取该字符串的指针
        wifi_ssid = "";
        wifi_pass = "";
    }
    else //未从网页读取到wifi
    {
        // Serial.println("用nvs保存的信息连接.");
        WiFi.begin(); // begin()不传入参数，默认连接上一次连接成功的wifi
    }

    int Connect_time = 0;                 //用于连接计时，如果长时间连接不成功，复位设备
    while (WiFi.status() != WL_CONNECTED) //等待WIFI连接成功
    {
        delay(500);
        Connect_time++;

        if (Connect_time > 2 * timeOut_s) //长时间连接不上，重新进入配网页面
        {
            // Serial.println(""); //主要目的是为了换行符
            // Serial.println("WIFI autoconnect fail, start AP for webconfig now...");

            TFT_Display_String_Select(CS2_PIN, 0, 0, "Web", TFT_GREEN, 2); //显示字符串
            wifiConfig();                                                  //开始配网功能
            return;                                                        //跳出 防止无限初始化
        }
    }

    if (WiFi.status() == WL_CONNECTED) //如果连接成功
    {
        // Serial.println("WIFI connect Success");
        // Serial.printf("SSID:%s", WiFi.SSID().c_str());
        // Serial.printf(", PSW:%s\r\n", WiFi.psk().c_str());
        // Serial.print("LocalIP:");
        // Serial.print(WiFi.localIP());
        // Serial.print(" ,GateIP:");
        // Serial.println(WiFi.gatewayIP());
        // Serial.print("WIFI status is:");
        // Serial.print(WiFi.status());
        // TFT_Display_String_Select(CS5_PIN, 0, 120, "OK   ", TFT_GREEN, 2); //显示字符串

        server.stop(); //停止开发板所建立的网络服务器。
    }
}

/* * 配置配网功能 */
void wifiConfig()
{
    initSoftAP();
    initDNS();
    initWebServer();
    scanWiFi();
}

/*
 * 删除保存的wifi信息，这里的删除是删除存储在flash的信息。删除后wifi读不到上次连接的记录，需重新配网
 */
void restoreWiFi()
{
    delay(500);
    esp_wifi_restore(); //删除保存的wifi信息
    // Serial.println("连接信息已清空,准备重启设备..");
    delay(10);
}

/* * 检查wifi是否已经连接 */
void checkConnect(bool reConnect)
{
    if (WiFi.status() != WL_CONNECTED) // wifi连接失败
    {
        if (reConnect == true && WiFi.getMode() != WIFI_AP && WiFi.getMode() != WIFI_AP_STA)
        {
            // Serial.println("WIFI未连接.");
            // Serial.println("WiFi Mode:");
            // Serial.println(WiFi.getMode());
            // Serial.println("正在连接WiFi...");
            connectToWiFi(connectTimeOut_s); //连接wifi函数
        }
    }
}

/* * 检测客户端DNS&HTTP请求 */
void checkDNS_HTTP()
{
    dnsServer.processNextRequest(); //检查客户端DNS请求
    server.handleClient();          //检查客户端(浏览器)http请求
}
