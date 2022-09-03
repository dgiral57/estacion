#include <sht30h.h>

void Sht30H::sample(){
    this->buffer.add(sht31.humidity);
    this->isReady = true;
}