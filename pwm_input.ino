#define DEBUG

#define CH_1_PIN 3
#define CH_2_PIN 4
#define CH_3_PIN 5
#define CH_4_PIN 6
#define INPUT_TIMEOUT 40000 // in microsecond

// Global Variables
int intCh1 = 0;
int intCh2 = 0;
int intCh3 = 0;
int intCh4 = 0;

char data[128];

void setup() {
  // 4 pwm inputs and output
  pinMode(CH_1_PIN, INPUT);
  pinMode(CH_2_PIN, INPUT);
  pinMode(CH_3_PIN, INPUT);
  pinMode(CH_4_PIN, INPUT);

  Serial.begin(115200);
  sprintf(data, "CH1 CH2 CH3 CH4");
  Serial.println(data);
}

int pulseInAndMap(byte ch) {
    // TODO: might use shift or mask to reduce precision
    return pulseIn(ch, HIGH, INPUT_TIMEOUT) / 10;
}

void readChannelInput() {
  intCh1 = pulseInAndMap(CH_1_PIN);
  intCh2 = pulseInAndMap(CH_2_PIN);
  intCh3 = pulseInAndMap(CH_3_PIN);
  intCh4 = pulseInAndMap(CH_4_PIN);
}

void loop() {
    readChannelInput();

    sprintf(data, "%d %d %d %d", intCh1, intCh2, intCh3, intCh4);
    Serial.println(data);
}
