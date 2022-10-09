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

int httpcode;
int httpCode;
long samplingTimer = millis();
long sendingTimer = millis();
u_int16_t samplingTime = 5000;
uint32_t sendingTime = 200000;
Sht30H sensorH(10,1,1);
Sht30T sensorT(10,1,1);
Bmp180P sensorP(10,1,1);
WIFI Wifi(ssid,psw);
HTTPClient http;
WiFiClient client;
String json;
//String url = "http://192.168.1.190:8080/values";
String url = "https://jsonplaceholder.typicode.com/users";

void setup() {
Serial.begin(115200);
Serial.println();
Wifi.cnct();
Serial.println(WiFi.subnetMask());
Serial.println("Conectando al servidor");


}
void loop() {
  if ((millis() - samplingTimer) > samplingTime){
    sensorH.sample();
    sensorT.sample();
    sensorP.sample();
    samplingTimer = millis();
  }

  if ((millis() - sendingTimer > sendingTime) || sensorH.state() || sensorT.state() || sensorP.state()){
    Serial.println("entro a enviar info");
    DynamicJsonDocument doc(2048);
    doc["temperature"] = sensorT.getValue();
    doc["humidity"] = sensorH.getValue();
    doc["pressure"] = sensorP.getValue();
    Serial.println("Creo el json");
    serializeJson(doc,json);
    Serial.println(json);
    http.begin(client,url) ;
    Serial.println("Coneccion creada");
    http.addHeader("Content-Type", "application/json");
    httpcode = http.GET();
    //httpCode = http.POST(json);
    Serial.print("el codigo http es:");
    Serial.println(httpcode);
    sensorH.reset_has_change();
    sensorT.reset_has_change();
    sensorP.reset_has_change();
    sendingTimer = millis();
    http.end();
  }
}