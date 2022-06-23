//
// Created by Daan Trommel on 20/04/2022.
//

#ifndef UNTITLED1_SENSOR_H
#define UNTITLED1_SENSOR_H

#include <Arduino.h>
#include "Multiplexer.h"

class Sensor {
public:
    Sensor(Multiplexer* multiplexer, int pin, int minValue, int maxValue);
    int getSensorValue();
    int getPercentageValue();
    void setMinValue(int minValue);
    void setMaxValue(int maxValue);

private:
    Multiplexer* _multiplexer = nullptr;
    int sensorPin;
    int minValue;
    int maxValue;
    int readSensor();
};


#endif //UNTITLED1_SENSOR_H
