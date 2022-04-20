//
// Created by Daan Trommel on 20/04/2022.
//

#include "Sensor.h"

Sensor::Sensor(int pin, int minValue, int maxValue) {
    powerPin = pin;
    this->minValue = minValue;
    this->maxValue = maxValue;
    pinMode(pin,OUTPUT);
    digitalWrite(pin,LOW);

}

int Sensor::getPercentageValue() {
    int percentage = map(readSensor(),maxValue,minValue,100,0);
    return percentage;
}

int Sensor::getSensorValue() {
    return readSensor();
}

void Sensor::activateSensor() {
    digitalWrite(powerPin,HIGH);
}

int Sensor::readSensor() {
    activateSensor();
    int sensorValue = analogRead(A0);
    deactivateSensor();
    return sensorValue;
}

void Sensor::deactivateSensor() {
    digitalWrite(powerPin,LOW);
}