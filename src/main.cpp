#include <Arduino.h>
#include <string.h>
#include <wifi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <sht30h.h>
#include <sht30t.h>
#include <bmp180p.h>
#include <ArduinoJson.h>

#define ssid  "motorola edge 20 lite_6907" // Declare your ID for WiFi connection
#define psw  "123456789" // Declare your password for WiFi connection

int httpcode;
int httpCode;
long samplingTimer = millis();
long sendingTimer = millis();
uint16_t samplingTime = 5000;
uint32_t sendingTime = 300000;
Sht30H sensorH(10,1,1);
Sht30T sensorT(10,1,1);
Bmp180P sensorP(10,1,1);
WIFI Wifi(ssid,psw);
HTTPClient http;
WiFiClient client;
String json;
String url = "http://192.168.149.94:8080/values";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Wifi.cnct();
}

void loop() {
  if ((millis() - samplingTimer) > samplingTime){
    sensorH.sample();
    sensorT.sample();
    sensorP.sample();
    samplingTimer = millis();
  }

  if ((millis() - sendingTimer > sendingTime) || sensorH.state() || sensorT.state() || sensorP.state()){
    DynamicJsonDocument doc(2048);
    doc["temperature"] = sensorT.getValue();
    doc["humidity"] = sensorH.getValue();
    doc["pressure"] = sensorP.getValue();
    serializeJson(doc,json);
    Serial.println(json);
    http.begin(client,url) ;
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(json);
    if (httpCode > 0){
    Serial.println(http.getString());
    }
    else{
      Serial.println("Error: Data not sent");
    }
    sensorH.reset_has_change();
    sensorT.reset_has_change();
    sensorP.reset_has_change();
    sendingTimer = millis();
    doc.clear();
    json.clear();
    http.end();
  }
}