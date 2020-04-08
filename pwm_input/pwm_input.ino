#include "Channel.h"

#define DEBUG
#define SINGLE_STICK
#define ROTATION 0.7071067812
#define THRESHOLD 64

#define CH_1_PIN 10
#define CH_2_PIN 11
#define CH_3_PIN 12
#define CH_4_PIN 13
#define PWM_INPUT_MIN 1090
#define PWM_INPUT_MAX 1890
#define INPUT_TIMEOUT 40000 // in microsecond

#define TRACK_LEFT_FORW 3
#define TRACK_LEFT_BACK 4
#define TRACK_RIGHT_FORW 7
#define TRACK_RIGHT_BACK 8
#define SERVO_PWM_MIN -256
#define SERVO_PWM_MAX  256

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

    int left = map(ch1.read(), PWM_INPUT_MIN, PWM_INPUT_MAX, SERVO_PWM_MIN, SERVO_PWM_MAX);
    int right = map(ch2.read(), PWM_INPUT_MIN, PWM_INPUT_MAX, SERVO_PWM_MIN, SERVO_PWM_MAX);

#ifdef SINGLE_STICK
    int x = left * ROTATION + right * ROTATION;
    int y = left * -ROTATION + right * ROTATION;
    left = constrain(x, SERVO_PWM_MIN, SERVO_PWM_MAX);
    right = constrain(y, SERVO_PWM_MIN, SERVO_PWM_MAX);
#endif

    if (!inputOutsideBound(left, right)) {
        // base on mode can make it go through a transform
        runTrack(enA, left, TRACK_LEFT_FORW, TRACK_LEFT_BACK);
        runTrack(enB, right, TRACK_RIGHT_FORW, TRACK_RIGHT_BACK);
    }

    sprintf(data, "%d %d %b", left, right, inputOutsideBound(left, right));
    Serial.println(data);
}
