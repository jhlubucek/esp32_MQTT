#include <Arduino.h>
#include "include/helper.h"

//reads input from serial port
void readSerial(char* var, int lenght)
{
  while (Serial.available() == 0) {
    // wait
  }
  Serial.readBytesUntil(10, var, lenght);
}