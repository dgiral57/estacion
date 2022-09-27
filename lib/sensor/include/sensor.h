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
    bool has_change;
    long last_time;
    float threshold;
    float sum;
    uint8_t pin;
    CircularBuffer buffer;
    bool chenged(float value);
    virtual float read(){ 
        return 0; 
        };
public:
    Sensor(){};
    Sensor(uint8_t size, float scale, float threshold);
    void sample();
    float getValue();
    bool state();
};

#endif