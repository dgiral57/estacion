#include <Arduino.h>
#include <sht30h.h>

long timer = millis();
Sht30H SensorH(10,1,1000);

void setup() {
Serial.begin(115200);
}
void loop() {
  if ((millis() - timer) > SensorH.interval){
    SensorH.sample();
    timer = millis();
  }

  if (Serial.available()){
    Serial.print("La humedad es: ");
    Serial.println(SensorH.getValue());
  }

}