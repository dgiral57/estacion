#include <Arduino.h>
#include <sht30h.h>

long samplingTimer = millis();
long sendingTimer = millis();
u_int16_t samplingTime = 1000;
uint32_t sendingTime = 300000;
Sht30H SensorH(10,1);

void setup() {
Serial.begin(115200);
}
void loop() {
  if ((millis() - samplingTimer) > samplingTime){
    SensorH.sample();
    samplingTimer = millis();
  }

  if ((millis() - sendingTimer > sendingTime) || SensorH.derivate()){
    Serial.println(SensorH.getValue());
    sendingTimer = millis();
  }
}