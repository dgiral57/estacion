#include <wifi.h>

WIFI::WIFI(String ssid, String psw) {
    this->ssid = ssid;
    this->psw = psw;
}

void WIFI::cnct(){
    WiFi.begin(this->ssid,this->psw);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("Connected");
}