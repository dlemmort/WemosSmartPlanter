//
// Created by Daan Trommel on 20/04/2022.
//

#ifndef UNTITLED1_PUMP_H
#define UNTITLED1_PUMP_H

#include <Arduino.h>

class Pump {
public:
    Pump(int pin);
    void giveWater(int seconds);
private:
    int pin;
};


#endif //UNTITLED1_PUMP_H
