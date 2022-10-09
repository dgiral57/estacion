#include <sht30t.h>

float Sht30T::read(){
    sht31.get();
    //Serial.print("Valor Temperatura: ");
    //Serial.println(sht31.cTemp);
    return sht31.cTemp;
}