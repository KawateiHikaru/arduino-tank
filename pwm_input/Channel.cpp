#include "Arduino.h"
#include "Channel.h"



Channel::Channel(int pin) {
    pinMode(pin, INPUT);
    _pin = pin;
    _firstRead = true;
    memset(&data, 0, SMOOTH_COUNT);
    idx=-1;
}

unsigned int Channel::read() {
    // todo: first read should populate all
    int val = pulseIn(_pin, HIGH, INPUT_TIMEOUT);

    // increment index and wrap around
    idx++;
    idx %= SMOOTH_COUNT;

    if (_firstRead) {
        memset(&data, val, 10);
        _firstRead = false;
    } else {
        data[idx] = val;
    }

    return smoothed();
}

unsigned int Channel::smoothed() {
    unsigned long total = 0;

    for (byte i=0;i<SMOOTH_COUNT;i++) {
        total += data[i];
    }

    return total / SMOOTH_COUNT;
}

unsigned int Channel::unsmoothed() {
    return data[idx];
}