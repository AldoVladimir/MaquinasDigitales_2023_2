#define PIN_BUTTON 34
int numberKeyPresses = 0;
int lastMillis = 0;

void IRAM_ATTR isrButton() {
  
  if (millis() - lastMillis > 10) {
    lastMillis = millis();
    numberKeyPresses += 1;    
  }
  // numberKeyPresses = numberKeyPresses + 1;
  // numberKeyPresses++;
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN_BUTTON, INPUT);
    attachInterrupt(PIN_BUTTON, isrButton, RISING);
}

void loop() {
    Serial.printf("El botón se ha presionado %u veces\n", numberKeyPresses);
    delay(100);
}
