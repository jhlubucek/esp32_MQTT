#include <Arduino.h>
#include "include/config.h"
#include "WiFi.h"
#include "PubSubClient.h"
#include "include/ConnectionService.h"


char eRead[40];
ConnectionService connectionService;




void setup() {
  Serial.begin(9600);

  pinMode(MODE_PIN, INPUT);
  if (digitalRead(MODE_PIN) == HIGH)
  {
    connectionService.setupThroughSerial();
  }
  pinMode (2, OUTPUT);
}
void loop() {
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
}