#define DEBUG

#define CH_PIN_1 3
#define CH_PIN_2 4
#define CH_PIN_3 5
#define CH_PIN_4 6
#define INPUT_TIMEOUT 40000 // in microsecond

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

int pulseInAndMap(byte ch) {
    // TODO: might use shift or mask to reduce precision
    return pulseIn(ch, HIGH, INPUT_TIMEOUT)/10;
}

void readChannelInput() {
  CH_1 = pulseInAndMap(CH_PIN_1);
  CH_2 = pulseInAndMap(CH_PIN_2);
  CH_3 = pulseInAndMap(CH_PIN_3);
  CH_4 = pulseInAndMap(CH_PIN_4);
}

void loop() {
    readChannelInput();

    sprintf(data, "%d %d %d %d", CH_1, CH_2, CH_3, CH_4);
    Serial.println(data);
}
