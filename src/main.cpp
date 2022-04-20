#include <Arduino.h>
#include "Sensor.h"
#include "Pump.h"

Sensor* waterLevelSensor = nullptr;
Sensor* soilMoistureSensor = nullptr;
Pump* waterPump = nullptr;

void setup() {
    waterLevelSensor = new Sensor(D3,670,985);
    soilMoistureSensor = new Sensor(D2,310,746);
    waterPump = new Pump(D1);
}

void loop() {
// write your code here
}