//
// Created by Daan Trommel on 25/04/2022.
//

#include "Multiplexer.h"

Multiplexer::Multiplexer(int pin1, int pin2, int pin3) {
    selectPins[0] = pin1;
    selectPins[1] = pin2;
    selectPins[2] = pin3;

    pinMode(pin1,OUTPUT);
    pinMode(pin2,OUTPUT);
    pinMode(pin3,OUTPUT);
}

int Multiplexer::ReadValue(int pin) {
    for (int i = 0; i < 3; i++){
        digitalWrite(selectPins[i], pin & (1 << i)?HIGH:LOW);
    }
    int analogValue = analogRead(A0);
    Serial.println(analogValue);
    return analogValue;
}