#define PIN_LED 7

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0;i<5;i++) {
    digitalWrite(PIN_LED, HIGH);
    delay(100);
    digitalWrite(PIN_LED, LOW);
    delay(100);
  }
  while(1) {
    digitalWrite(PIN_LED, HIGH);
  }
}
