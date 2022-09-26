#ifndef WIFI_CONN
#define WIFI_CONN

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <string.h>

class WIFI
{
private:
    String ssid;
    String psw;
public:
    WIFI(String ssid, String psw);
    void cnct();
};

#endif