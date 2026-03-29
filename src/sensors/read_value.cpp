#include "pyranometer_value.h"

Adafruit_ADS1115 ads;

void initPyranometer() {
  ads.begin();
}

float readVoltage() {
  //we should connect to the A0 on the ADS1115 //ads.readADC_SingleEnded(0);
  //the result of the ads.readADC_SingleEnded(0); is the Digital Value not voltage
  int16_t rawValue = ads.readADC_SingleEnded(0);
  //at ADS1115 per 1 bit is 0.1875mv
  float voltage = rawValue * 0.1875 / 1000.0;
  
  return voltage;
}
//we want the Irradiance 
//Irradiance (W/m²) = Voltage (µV) / Sensitivity
//Sensitivity = 10 µV / (W/m²)

//after we read the voltage got from sensor we should to convert it to micro volt
//µV = V × 1,000,000


/*
*********************************************** 
we can know the Sensitivity from datasheet of the sensor
*********************************************** 

*/
float readIrradiance() {
  float voltage_mV = readVoltage() * 1000.0;  
  float irradiance = voltage_mV / SENSITIVITY; // W/m²
  //irradiance of the sun 
  return irradiance;
}

/* sun status*/
String getSunStatus(float irradiance) {
  if (irradiance < 10)        return "Night / No Sun";
  else if (irradiance < 200)  return "Sunrise or Sunset";
  else if (irradiance < 600)  return "Sun Present - Cloudy";
  else                        return "Full Sun - Clear Sky";
}