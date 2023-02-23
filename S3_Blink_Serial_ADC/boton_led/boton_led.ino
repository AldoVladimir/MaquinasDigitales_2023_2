//Cuando presiono el boton, LED se enciende
#define PIN_LED 33
#define PIN_BUTTON 34

void setup() {
  pinMode(PIN_LED,OUTPUT);
  pinMode(PIN_BUTTON,INPUT);

  Serial.begin(115200);
}

void loop() {
  bool button_status = digitalRead(PIN_BUTTON);
  Serial.println(button_status);

  if (button_status){
    digitalWrite(PIN_LED,HIGH);
  }
  else{
    digitalWrite(PIN_LED,LOW);
  }
  
  delay(10);
}
