#include <Arduino.h>
#include <Dobot.h>
Dobot myDobot;

void setup() {
  Serial.begin(115200);
  myDobot.begin();
}
