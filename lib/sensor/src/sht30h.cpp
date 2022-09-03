#include <sht30h.h>

void Sht30H::sample(){
    sht31.get();
    this->buffer.add(sht31.humidity);
    this->isReady = true;
}

float Sht30H::getInterval(){
    return this->interval;
}