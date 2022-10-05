#include <Arduino.h>
#include <string.h>
#include <wifi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <sht30h.h>
#include <ArduinoJson.h>

#define ssid  "TIGO0B9491" // Declare your ID for WiFi connection
#define psw  "29VY4BAJ" // Declare your password for WiFi connection


long samplingTimer = millis();
long sendingTimer = millis();
u_int16_t samplingTime = 5000;
uint32_t sendingTime = 200000;
Sht30H sensorH(10,1,1);
WIFI Wifi(ssid,psw);
HTTPClient http;
WiFiClient client;
String json;


void setup() {
Serial.begin(115200);
Serial.println();
//Wifi.cnct();
}
void loop() {
  if ((millis() - samplingTimer) > samplingTime){
    sensorH.sample();
    samplingTimer = millis();
  }

  if ((millis() - sendingTimer > sendingTime) || sensorH.state()){
    // Prepare JSON document
    DynamicJsonDocument doc(2048);
    //doc["Temperature"] = sensorT.getValue();
    doc["Humidity"] = sensorH.getValue();
    //doc["Pressure"] = sensorP.getValue()
    http.begin(client,"http://0.0.0.0:8080/Values");
    http.addHeader("Content-Type", "application/json");
    serializeJson(doc,json);
    int httpCode = http.POST(json);
    sensorH.reset_has_change();
    sendingTimer = millis();
    Serial.println(httpCode);
  }
}