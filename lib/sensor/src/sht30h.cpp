#include <sht30h.h>

float Sht30H::read(){
    sht31.get();
    //Serial.print("Valor Humedad: ");
    //Serial.println(sht31.humidity);
    return sht31.humidity;
}