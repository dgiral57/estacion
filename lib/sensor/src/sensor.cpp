#include <sensor.h>

Sensor::Sensor(uint8_t size, float scale){
    this->value = 0;
    this->isReady = false;
    this->scale = scale;
    this->buffer = CircularBuffer(size);
}

float Sensor::getValue(){
    if(this->isReady){
        this->value = buffer.mean() * this->scale;
        return this->value;
    }
    return this->value;
}