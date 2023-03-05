//Presion en una columna, temperatura en otra
//Ejemplo
//70000,23.5
//70000,23.6

#include "Adafruit_BMP280.h"

Adafruit_BMP280 bmp; //Objeto bmp
char payload [80]; //payload de lecturas

void setup() {
  bmp.begin(0x76); //Inicializa bmp
  Serial.begin(115200);
}

void loop() {

  /* Ok, pero no es escalable
  Serial.print(bmp.readTemperature());
  Serial.print(",");
  Serial.println(bmp.readPressure()/1000); //kPa
  */

  //Guardar las lecturas en 
  float pressure = bmp.readPressure();
  float temperature = bmp.readTemperature();


  //Hacer el payload de lecturas de sensores
  sprintf(payload,"%6.2f,%3.2f",
          pressure,
          temperature);

  Serial.println(payload);
  //mandar_a_sd(payload);
  //mandar_a_aws(payload);  

  delay(200);
}