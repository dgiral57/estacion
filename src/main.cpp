#include <Arduino.h>
#include <string.h>
#include <wifi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <sht30h.h>

#define ssid  "TIGO0B9491" // Declare your ID for WiFi connection
#define psw  "29VY4BAJ" // Declare your password for WiFi connection


long samplingTimer = millis();
long sendingTimer = millis();
u_int16_t samplingTime = 1000;
uint32_t sendingTime = 300000;
Sht30H SensorH(10,1);
WIFI Wifi(ssid,psw);
HTTPClient http;
WiFiClient Client;

void setup() {
Serial.begin(115200);
Wifi.cnct();
}
void loop() {
  if ((millis() - samplingTimer) > samplingTime){
    SensorH.sample();
    samplingTimer = millis();
  }

  if ((millis() - sendingTimer > sendingTime) || SensorH.derivate()) {
    http.begin(Client,"http://0.0.0.0:8080/Values");
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");
  }
}