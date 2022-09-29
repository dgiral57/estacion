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
    else{
        return this->value;
    }
    
}

bool Sensor::chenged(float value){
    Serial.println("Entro a chenged()");
    Serial.print("value: ");
    Serial.println(value);
    float time = (millis() - this->last_time) / 1000;
    Serial.print("time: ");
    Serial.println(time);
    float last_value = this->getValue();
    Serial.print("Last value: ");
    Serial.println(last_value);
    float diff = ((value * this->scale)-last_value)/time;
    Serial.print("diff: ");
    Serial.println(diff);
    this->sum += diff;
    Serial.print("sum: ");
    Serial.println(this->sum);
    Serial.println();
    if (abs(this->sum) >= this->threshold){
        this->sum = 0;
        return true;
    }
    else {
        return false;
    }
}

void Sensor::sample(){
    float value = this->read();
    Serial.println("Dato captuado");
    this->has_change = this->chenged(value);
    this->buffer.add(value);
    this->isReady = true;
    this->last_time = millis();

}

bool Sensor::state(){
    return this->has_change;
}

void Sensor::reset_has_change(){
    this->has_change = 0;
}

