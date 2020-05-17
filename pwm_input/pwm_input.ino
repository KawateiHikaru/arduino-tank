#include "Channel.hpp"

#define DEBUG
#define SINGLE_STICK
#define ROTATION 0.7071067812
#define THRESHOLD 64

#define CH_1_PIN 10
#define CH_2_PIN 11
#define CH_3_PIN 12

#define PWM_INPUT_MIN 1080
#define PWM_INPUT_MID 1480
#define PWM_INPUT_MAX 1880
#define INPUT_TIMEOUT 40000 // in microsecond

#define TRACK_LEFT_FORW 3
#define TRACK_LEFT_BACK 4
#define enA 5
#define enB 6
#define TRACK_RIGHT_FORW 7
#define TRACK_RIGHT_BACK 8

#define STICK_PWM_MIN -250
#define STICK_PWM_MAX 250

#define SERVO_PWM_MIN -250
#define SERVO_PWM_MAX 250

char data[128];

Channel Ch1(CH_1_PIN);
Channel Ch2(CH_2_PIN);
// Channel pwmCh3(CH_3_PIN);

void setup()
{

  // Ch1.begin(true);
  // Ch2.begin(true);
  // pwmCh3.begin(true);
  delay(5000);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(TRACK_LEFT_FORW, OUTPUT);
  pinMode(TRACK_LEFT_BACK, OUTPUT);
  pinMode(TRACK_RIGHT_FORW, OUTPUT);
  pinMode(TRACK_RIGHT_BACK, OUTPUT);

  Serial.begin(9600);
  Serial.println("CH1 CH2");
}

void runTrack(byte PIN, int pwm, byte TRACK_A, byte TRACK_B)
{

  if (pwm > THRESHOLD)
  {
    digitalWrite(TRACK_A, LOW);
    digitalWrite(TRACK_B, HIGH);
  }
  else if (pwm < -THRESHOLD)
  {
    digitalWrite(TRACK_A, HIGH);
    digitalWrite(TRACK_B, LOW);
  }

  analogWrite(PIN, abs(pwm));
}

bool inputOutsideBound(int left, int right)
{
  return (left >= SERVO_PWM_MAX ||
          left <= SERVO_PWM_MIN ||
          right >= SERVO_PWM_MAX ||
          right <= SERVO_PWM_MIN);
}

void loop()
{
  int steer = 0, throttle = 0, left = 0, right = 0;

  int ch1 = Ch1.getValue();
  int ch2 = Ch2.getValue();

  if (ch1 == 0 || ch2 == 0)
  {
    delay(1000);
  }
  else
  {

    steer = map(ch1, PWM_INPUT_MIN, PWM_INPUT_MAX, STICK_PWM_MIN, STICK_PWM_MAX);
    throttle = map(ch2, PWM_INPUT_MIN, PWM_INPUT_MAX, STICK_PWM_MIN, STICK_PWM_MAX);

    if (throttle > -THRESHOLD && throttle < THRESHOLD)
    {
      left = steer;
      right = -steer;
    }
    else
    {
      if (throttle < -THRESHOLD)
      {
        steer = -steer;
      }
      // apply the steer on throttle
      left = throttle;
      right = throttle;

      if (steer < -THRESHOLD)
      {
        right = throttle - abs(steer);
        if (right < 0) right = 0;
      }
      else if (steer > THRESHOLD)
      {
        left = (throttle - abs(steer));
        if (left < 0) left = 0;
      }
    }

    left = constrain(left, SERVO_PWM_MIN, SERVO_PWM_MAX);
    right = constrain(right, SERVO_PWM_MIN, SERVO_PWM_MAX);

    {
      // base on mode can make it go through a transform
      runTrack(enA, left, TRACK_LEFT_FORW, TRACK_LEFT_BACK);
      runTrack(enB, right, TRACK_RIGHT_FORW, TRACK_RIGHT_BACK);
    }
  }
  sprintf(data, "%d %d %d %d %d %d", ch1, ch2, steer, throttle, left, right);
  Serial.println(data);
}
