#include "Channel.h"

#define DEBUG

#define CH_1_PIN 10
#define CH_2_PIN 11
#define CH_3_PIN 12
#define CH_4_PIN 13
#define INPUT_TIMEOUT 40000 // in microsecond

#define TRACK_LEFT_FORW 3
#define TRACK_LEFT_BACK 4
#define TRACK_RIGHT_FORW 7
#define TRACK_RIGHT_BACK 8

#define enA 5
#define enB 6

char data[128];


// 1090-1490-1890
Channel ch1(CH_1_PIN);
Channel ch2(CH_2_PIN);
Channel ch3(CH_3_PIN);


void setup() {

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);

    pinMode(TRACK_LEFT_FORW, OUTPUT);
    pinMode(TRACK_LEFT_BACK, OUTPUT);
    pinMode(TRACK_RIGHT_FORW, OUTPUT);
    pinMode(TRACK_RIGHT_BACK, OUTPUT);

    Serial.begin(115200);
}

int runTrack(byte PIN, int input, byte TRACK_A, byte TRACK_B) {
    int pwm = map(input, 1090, 1890, -256, 256);

    if (pwm > 60) {
        digitalWrite(TRACK_A, LOW);
        digitalWrite(TRACK_B, HIGH);
    } else if (pwm < -60) {
       digitalWrite(TRACK_A, HIGH);
       digitalWrite(TRACK_B, LOW);
    } else  {
      digitalWrite(TRACK_A, HIGH);
      digitalWrite(TRACK_B, HIGH);
   }

    pwm = abs(pwm);
    analogWrite(PIN, pwm);

    return pwm;
}

void loop() {

    int left = runTrack(enA, ch1.read(), TRACK_LEFT_FORW, TRACK_LEFT_BACK);
    int right = runTrack(enB, ch2.read(), TRACK_RIGHT_FORW, TRACK_RIGHT_BACK);

    sprintf(data, "%d %d", left, right);
    Serial.println(data);
}
