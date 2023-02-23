//Plotear la señal resultante de oscurecer e iluminar el LDR
#define PIN_LED 33
#define PIN_LDR 35
#define THRLD 800

void setup() {
  pinMode(PIN_LED,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int ldr_signal = analogRead(PIN_LDR);  

  if(ldr_signal>THRLD){
    digitalWrite(PIN_LED, LOW);
  }
  else{
    digitalWrite(PIN_LED, HIGH);
  }
  
  Serial.println(ldr_signal);
  delay(50);
}
