#include <bmp180p.h>


float Bmp180P::read(){
    bmp180pr.getPressure();
    Serial.print("Valor Presión: ");
    Serial.println(bmp180pr.getPressure());
    return bmp180pr.getPressure();
}