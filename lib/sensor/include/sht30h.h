#ifndef SHT30H
#define SHT30H

#include <sensor.h>
#include <Arduino.h>
#include <Wire.h>
#include <WEMOS_SHT3X.h>


class Sht30H : public Sensor
{
private:
    SHT3X sht31;
    float interval;
public:
    Sht30H(uint8_t size, float scale, float interval):Sensor(size,scale)
    {
        SHT3X sht31();
        this->interval = interval;
    }
    void sample();
    float getInterval();
};

#endif