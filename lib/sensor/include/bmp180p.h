#ifndef BMP180P
#define BMP180P

#include <sensor.h>
#include <Wire.h>
#include <BMP180.h>


class Bmp180P : public Sensor
{
private:
    BMP180 bmp180pr;
    float read();
public:
    Bmp180P(uint8_t size, float scale, float threshold):Sensor(size,scale,threshold){
        this->bmp180pr = BMP180();
    };
};

#endif