#include <sensor.h>

Sensor::Sensor(uint8_t size, float scale){
    this->value = 0;
    this->isReady = false;
    this->scale = scale;
    this->size = size;
    this->buffer = CircularBuffer(size);
}

float Sensor::getValue(){
    if(this->isReady){
        this->value = buffer.mean() * this->scale;
        return this->value;
    }
    return this->value;
}

bool Sensor::derivate(){
    if (abs(this->buffer.mean() * this->scale  - this->value) > 1) {
            return true;
    }
    else {
        return false;
    }
}


