#include <AUnit.h>
#include "Channel.h"

#define DEBUG

#define CH_1_PIN 3
#define CH_2_PIN 4
#define CH_3_PIN 5
#define CH_4_PIN 6
#define INPUT_TIMEOUT 40000 // in microsecond

#define TRACK_LEFT_FORW 10
#define TRACK_LEFT_BACK 11
#define TRACK_RIGHT_FORW 12
#define TRACK_RIGHT_BACK 13

#define enA 9
#define enB 10

char data[128];

Channel ch1(CH_1_PIN);
/*
Channel ch2(CH_2_PIN);
Channel ch3(CH_3_PIN);
Channel ch4(CH_4_PIN);
*/


void setup() {

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);

  Serial.begin(115200);
//  sprintf(data, "CH1 CH2 CH3 CH4");
//  Serial.println(data);
}

int speed=0;

void loop() {
Serial.println(speed);
analogWrite(enA, speed);
analogWrite(enB, speed);
speed+=1;
speed %=256;
delay(200);

    // aunit::TestRunner::run();
    // readChannelInput();

//    sprintf(data, "%d %d", ch1.read(), ch1.unsmoothed());
//    Serial.println(data);
}
