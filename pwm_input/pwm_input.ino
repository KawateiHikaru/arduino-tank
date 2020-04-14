#include "Channel.h"

#define DEBUG
#define SINGLE_STICK
#define ROTATION 0.7071067812
#define THRESHOLD 64

#define CH_1_PIN 10
#define CH_2_PIN 11
#define CH_3_PIN 12
#define CH_4_PIN 13
#define PWM_INPUT_MIN 1100
#define PWM_INPUT_MID 1500
#define PWM_INPUT_MAX 1900
#define INPUT_TIMEOUT 40000 // in microsecond

#define TRACK_LEFT_FORW 4
#define TRACK_LEFT_BACK 5
#define enA 6
#define TRACK_RIGHT_FORW 7
#define TRACK_RIGHT_BACK 8
#define enB 9

#define STICK_PWM_MIN -360
#define STICK_PWM_MAX  360

#define SERVO_PWM_MIN -255
#define SERVO_PWM_MAX  255

char data[128];


// 70-95-120 25 apart
Channel pwmCh1(CH_1_PIN);
Channel pwmCh2(CH_2_PIN);
//Channel ch3(CH_3_PIN);


void setup() {

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);

    pinMode(TRACK_LEFT_FORW, OUTPUT);
    pinMode(TRACK_LEFT_BACK, OUTPUT);
    pinMode(TRACK_RIGHT_FORW, OUTPUT);
    pinMode(TRACK_RIGHT_BACK, OUTPUT);

    Serial.begin(9600);
    Serial.println("CH1 CH2");
}

void runTrack(byte PIN, int pwm, byte TRACK_A, byte TRACK_B) {

    if (pwm > THRESHOLD) {
        digitalWrite(TRACK_A, LOW);
        digitalWrite(TRACK_B, HIGH);
    } else if (pwm < -THRESHOLD) {
       digitalWrite(TRACK_A, HIGH);
       digitalWrite(TRACK_B, LOW);
    } else  {
      digitalWrite(TRACK_A, HIGH);
      digitalWrite(TRACK_B, HIGH);
    }

    pwm = abs(pwm);
    analogWrite(PIN, pwm);
}

bool inputOutsideBound(int left, int right) {
    return (left >= SERVO_PWM_MAX ||
            left <= SERVO_PWM_MIN ||
           right >= SERVO_PWM_MAX ||
           right <= SERVO_PWM_MIN);
}

void loop() {
    int left, right, x, y;

    int ch1 = pwmCh1.read();
    int ch2 = pwmCh2.read();


#ifdef SINGLE_STICK

    left  = map(ch1, PWM_INPUT_MIN, PWM_INPUT_MAX, STICK_PWM_MIN, STICK_PWM_MAX);
    right = map(ch2, PWM_INPUT_MIN, PWM_INPUT_MAX, STICK_PWM_MIN, STICK_PWM_MAX);

    if (right < 0 ) left = -left;

    x = left * ROTATION + right * ROTATION;
    y = left * -ROTATION + right * ROTATION;

    left = constrain(x, SERVO_PWM_MIN, SERVO_PWM_MAX);
    right = constrain(y, SERVO_PWM_MIN, SERVO_PWM_MAX);
#endif


    if (!inputOutsideBound(left, right))
    {
        // base on mode can make it go through a transform
        runTrack(enA, left, TRACK_LEFT_FORW, TRACK_LEFT_BACK);
        runTrack(enB, right, TRACK_RIGHT_FORW, TRACK_RIGHT_BACK);
    }

    sprintf(data, "%d %d %d %d %d %d", ch1, ch2, left, right, x, y);
    Serial.println(data);
}
