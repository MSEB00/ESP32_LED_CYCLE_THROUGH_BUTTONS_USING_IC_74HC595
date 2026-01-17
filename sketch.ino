#define DATA_PIN   18
#define CLOCK_PIN  5
#define LATCH_PIN  19

#define NEXT_BTN   4
#define PREV_BTN   15

uint8_t currentLed = 0;
bool lastNextState = HIGH;
bool lastPrevState = HIGH;

void shiftOut16(uint16_t data) {
  digitalWrite(LATCH_PIN, LOW);

  for (int i = 15; i >= 0; i--) {
    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(DATA_PIN, (data >> i) & 0x01);
    digitalWrite(CLOCK_PIN, HIGH);
  }

  digitalWrite(LATCH_PIN, HIGH);
}

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  pinMode(NEXT_BTN, INPUT_PULLUP);
  pinMode(PREV_BTN, INPUT_PULLUP);

  shiftOut16(1 << currentLed); // Start at LED 0
}

void loop() {
  bool nextState = digitalRead(NEXT_BTN);
  bool prevState = digitalRead(PREV_BTN);

  // NEXT button (HIGH → LOW)
  if (lastNextState == HIGH && nextState == LOW) {
    currentLed++;
    if (currentLed >= 16) currentLed = 0;

    shiftOut16(1 << currentLed);
    delay(200); // debounce
  }

  // PREV button (HIGH → LOW)
  if (lastPrevState == HIGH && prevState == LOW) {
    if (currentLed == 0) currentLed = 15;
    else currentLed--;

    shiftOut16(1 << currentLed);
    delay(200); // debounce
  }

  lastNextState = nextState;
  lastPrevState = prevState;
}
