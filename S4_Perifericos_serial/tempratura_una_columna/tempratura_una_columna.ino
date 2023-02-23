//Temperatura en serial plotter
#include "Adafruit_BMP280.h"

Adafruit_BMP280 bmp; //Objeto bmp


void setup() {
  bmp.begin(0x76); //Inicializa bmp
  Serial.begin(115200);

}

void loop() {
  Serial.println(bmp.readTemperature());
  delay(200);
}
