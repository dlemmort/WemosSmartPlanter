//
// Created by Daan Trommel on 20/04/2022.
//

#include "Pump.h"

Pump::Pump(int pin) {
    this->pin = pin;
    pinMode(pin,OUTPUT);
    digitalWrite(pin,LOW);
}

void Pump::giveWater(int seconds) {
    digitalWrite(pin,HIGH);
    delay(seconds*1000);
    digitalWrite(pin,LOW);
}