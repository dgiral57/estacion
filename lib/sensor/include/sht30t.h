#ifndef SHT30T
#define SHT30T

#include <sensor.h>
#include <Wire.h>
#include <WEMOS_SHT3X.h>


class Sht30T : public Sensor
{
private:
    SHT3X sht31;
    float read();
public:
    Sht30T(uint8_t size, float scale, float threshold):Sensor(size,scale,threshold){
        this->sht31 = SHT3X();
    };
};

#endif