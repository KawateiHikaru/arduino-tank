#ifndef Channel_h
#define Channel_h

#include "Arduino.h"
#define INPUT_TIMEOUT 40000 // in microsecond
#define SMOOTH_COUNT 10
#define GRANULARITY 1

class Channel
{
    public:
        Channel(int pin);
        void setup();
        unsigned int read();
        unsigned int smoothed();
        unsigned int unsmoothed();
    private:
        bool _firstRead;
        int _pin;
        int data[SMOOTH_COUNT];
        byte idx;
};

#endif