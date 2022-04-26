//
// Created by Daan Trommel on 25/04/2022.
//

#ifndef WEMOSSMARTPLANTER_MULTIPLEXER_H
#define WEMOSSMARTPLANTER_MULTIPLEXER_H

#include <Arduino.h>

class Multiplexer {
public:
    Multiplexer(int pin1, int pin2, int pin3);
    int ReadValue(int pin);

private:
    int selectPins[3];
};


#endif //WEMOSSMARTPLANTER_MULTIPLEXER_H
