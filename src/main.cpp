#include <Arduino.h>
#include <Wire.h>
#include "pyranometer_value.h"

void setup() {
  Serial.begin(9600);
  initPyranometer();
}

void loop() {
  float voltage = readVoltage();
  float irradiance  = readIrradiance();

  Serial.print("Voltage: ");
  Serial.print(voltage, 4);

  Serial.print(" V  |  Irradiance: ");
  Serial.print(irradiance, 2);
  Serial.println(" W/m²");

  /************************************************** */
  String status = getSunStatus(irradiance);
Serial.println("Sun Status: " + status);


  if (irradiance >= 200) {
    turnRelayON();
    Serial.println("Relay: ON");
  } else {
    turnRelayOFF();
    Serial.println("Relay: OFF");
  }
  delay(1000);
}