#ifndef SHT30H
#define SHT30H

#include <sensor.h>
#include <Wire.h>
#include <WEMOS_SHT3X.h>


class Sht30H : public Sensor
{
private:
    SHT3X sht31;
public:
    Sht30H(uint8_t size, float scale):Sensor(size,scale)
    {
        SHT3X sht31();
    }
    void sample();
};

#endif