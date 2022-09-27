#include <sensor.h>
#include <stdlib.h>
#include <Arduino.h>

Sensor::Sensor(uint8_t size, float scale, float threshold){
    this->value = 0;
    this->sum = 0;
    this->isReady = false;
    this->has_change = false;
    this->scale = scale;
    this->threshold = threshold;
    this->buffer = CircularBuffer(size);
    this->last_time = millis();
}

float Sensor::getValue(){
    if(this->isReady){
        this->value = buffer.mean() * this->scale;
        return this->value;
    }
    return this->value;
}

void Sensor::sample(){
    this->isReady = true;
    float value = this->read();
    this->has_change = this->chenged(value);
    this->buffer.add(value);
    this->last_time = millis();

}

bool Sensor::chenged(float value){
    float time = (millis() - this->last_time) * 1000;
    float last_value = this->getValue();
    float diff = ((value * this->scale)-last_value)/time;
    this->sum += abs(diff);
    if (this->sum >= this->threshold){
        this->sum = 0;
        return true;
    }
    else {
        return false;
    }
}

bool Sensor::state(){
    return this->has_change;
}

