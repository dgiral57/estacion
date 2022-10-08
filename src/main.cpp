#include <Arduino.h>
#include <string.h>
#include <wifi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <sht30h.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <sht30t.h>
#include <bmp180p.h>

#define ssid  "TIGO0B9491" // Declare your ID for WiFi connection
#define psw  "29VY4BAJ" // Declare your password for WiFi connection
#define url "http://192.168.1.190:8080/Values"


long samplingTimer = millis();
long sendingTimer = millis();
u_int16_t samplingTime = 5000;
uint32_t sendingTime = 200000;
Sht30H sensorH(10,1,1);
Sht30T SensorT(10,1,1);
Bmp180P SensorP(10,1,1);
WIFI Wifi(ssid,psw);
HTTPClient http;
WiFiClient client;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String json;


void setup() {
Serial.begin(115200);
Serial.println();
Wifi.cnct();
timeClient.begin();

}
void loop() {
  if ((millis() - samplingTimer) > samplingTime){
    sensorH.sample();
    SensorT.sample();
    SensorP.sample();
    samplingTimer = millis();
  }

  if ((millis() - sendingTimer > sendingTime) || SensorH.state() || SensorT.state() || SensorP.state()){
    DynamicJsonDocument doc(2048);
    doc["humidity"] = sensorH.getValue();
    //doc["Temperature"] = sensorT.getValue();
    //doc["Pressure"] = sensorP.getValue()
    http.begin(client,url);
    http.addHeader("Content-Type", "application/json");
    serializeJson(doc,json);
    int httpCode = http.POST(json);
    sensorH.reset_has_change();
    sendingTimer = millis();
    Serial.println(httpCode);
  }
}