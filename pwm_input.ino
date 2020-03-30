#define DEBUG

#define CH_PIN_1 3
#define CH_PIN_2 4
#define CH_PIN_3 5
#define CH_PIN_4 6

// Global Variables
int CH_1 = 0;
int CH_2 = 0;
int CH_3 = 0;
int CH_4 = 0;

char data[128];

void setup() {
  // 4 pwm inputs and output
  pinMode(CH_PIN_1, INPUT);
  pinMode(CH_PIN_2, INPUT);
  pinMode(CH_PIN_3, INPUT);
  pinMode(CH_PIN_4, INPUT);

  Serial.begin(115200);
  sprintf(data, "CH1 CH2 CH3 CH4");
  Serial.println(data);
}

void readChannelInput() {
    // TODO: might use shift or mask to reduce precision
  CH_1 = pulseIn(CH_PIN_1, HIGH) / 10;
  CH_2 = pulseIn(CH_PIN_2, HIGH) / 10;
  CH_3 = pulseIn(CH_PIN_3, HIGH) / 10;
  CH_4 = pulseIn(CH_PIN_4, HIGH) / 10;
}


void loop() {
    readChannelInput();

    sprintf(data, "%d %d %d %d", CH_1, CH_2, CH_3, CH_4);
    Serial.println(data);

}
