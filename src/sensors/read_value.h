#ifndef pyranometer
#define pyranometer


#include <Adafruit_ADS1X15.h>
#define SENSITIVITY 5.0  // mV per W/m² —on datasheet
void initPyranometer();
float readVoltage();
float readIrradiance();
String getSunStatus(float irradiance);

#endif