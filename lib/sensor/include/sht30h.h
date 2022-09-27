#ifndef SHT30H
#define SHT30H

#include <sensor.h>
#include <Wire.h>
#include <WEMOS_SHT3X.h>


class Sht30H : public Sensor
{
private:
    SHT3X sht31;
    float read();
public:
    Sht30H(uint8_t size, float scale, float threshold):Sensor(size,scale,threshold)    {
        this->sht31 = SHT3X();
    };
};

#endif