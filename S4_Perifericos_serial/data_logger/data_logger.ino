#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "Adafruit_BMP280.h"

//Loguear la info dle sensor barometrico y LDR
#define LED_PIN 33
#define LDR_PIN 35

File readings;
Adafruit_BMP280 bmp; //Objeto bmp

char payload [80]; //payload de lecturas

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  bmp.begin(0x76);
  //Montarlo. Si falla, manda mensaje de error
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }
}

void loop() {

  //Guardar las lecturas en 
  float pressure = bmp.readPressure();
  float temperature = bmp.readTemperature();
  int luminosity = analogRead(LDR_PIN);

  //Hacer el payload de lecturas de sensores
  sprintf(payload,"%6.2f,%3.2f,%d",
          pressure,
          temperature,
          luminosity);

  digitalWrite(LED_PIN,HIGH);
    readings = SD.open("/lecturas_sensor.csv",FILE_APPEND);
    readings.println(payload);
    readings.close();
    Serial.println(payload);
  digitalWrite(LED_PIN,LOW);

  delay(500);  

}
