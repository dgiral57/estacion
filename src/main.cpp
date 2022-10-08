#include <Arduino.h>
#include <string.h>
#include <wifi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <sht30h.h>
#include <sht30t.h>
#include <bmp180p.h>

#define ssid  "TIGO0B9491" // Declare your ID for WiFi connection
#define psw  "29VY4BAJ" // Declare your password for WiFi connection


long samplingTimer = millis();
long sendingTimer = millis();
u_int16_t samplingTime = 5000;
uint32_t sendingTime = 200000;
Sht30H SensorH(10,1,1);
Sht30T SensorT(10,1,1);
Bmp180P SensorP(10,1,1);
WIFI Wifi(ssid,psw);
HTTPClient http;
WiFiClient Client;

void setup() {
Serial.begin(115200);
Serial.println();
//Wifi.cnct();
}
void loop() {
  if ((millis() - samplingTimer) > samplingTime){
    SensorH.sample();
    SensorT.sample();
    SensorP.sample();
    samplingTimer = millis();
  }

  if ((millis() - sendingTimer > sendingTime) || SensorH.state() || SensorT.state() || SensorP.state()){
    Serial.print("state: ");
    Serial.println(SensorH.state());
    Serial.print("Sensor value: ");
    Serial.println(SensorH.getValue());
    Serial.println();
    SensorH.reset_has_change();
    sendingTimer = millis();
  }
}