#ifndef SENSOR
#define SENSOR

#include <circular.h>
#include <stdint.h>
#include <Arduino.h>

class Sensor
{
protected:
    float value;
    float scale;
    bool isReady;
    int size;
    uint8_t pin;
    CircularBuffer buffer;
public:
    Sensor(){};
    Sensor(uint8_t size, float scale);
    virtual void sample(){};
    float getValue();
    bool derivate();
};

#endif