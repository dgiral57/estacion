#include <sht30h.h>

float Sht30H::read(){
    sht31.get();
    return sht31.humidity;
}