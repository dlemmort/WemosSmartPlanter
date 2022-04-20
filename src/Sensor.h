//
// Created by Daan Trommel on 20/04/2022.
//

#ifndef UNTITLED1_SENSOR_H
#define UNTITLED1_SENSOR_H

#include <Arduino.h>

class Sensor {
public:
    Sensor(int pin, int minValue, int maxValue);
    int getSensorValue();
    int getPercentageValue();

private:
    int powerPin;
    int minValue;
    int maxValue;
    void activateSensor();
    int readSensor();
    void deactivateSensor();
};


#endif //UNTITLED1_SENSOR_H
