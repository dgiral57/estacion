#include <wifi.h>

WIFI::WIFI(String ssid, String psw) {
    this->ssid = ssid;
    this->psw = psw;
}

void WIFI::cnct(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(this->ssid,this->psw);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.println("Connected");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Subnet Mask: ");
    Serial.println(WiFi.subnetMask());
}