#include "relay_control.h"
#include <Arduino.h>

void initRelay() {
  pinMode(RELAY_PIN, OUTPUT);
  turnRelayOFF();  // نبدأ والريلاي مطفي
}

void turnRelayON() {
  digitalWrite(RELAY_PIN, LOW);   // Active LOW
}

void turnRelayOFF() {
  digitalWrite(RELAY_PIN, HIGH);  // Active LOW
}