#include <Arduino.h>
#include "EEPROM.h"
#include "include/EpromService.h"

EpromService::EpromService(){
  startEprom();
}

void EpromService::startEprom()
{
  EEPROM.begin(512);
}

// Saves string do EEPROM
void EpromService::SaveString(int startAt, const char* id)
{
  for (byte i = 0; i <= strlen(id); i++)
  {
    EEPROM.write(i + startAt, (uint8_t) id[i]);
  }
  EEPROM.commit();
}

// Reads string from EEPROM
void EpromService::ReadString(byte startAt, byte bufor, char* eRead)
{
  for (byte i = 0; i <= bufor; i++)
  {
    eRead[i] = (char)EEPROM.read(i + startAt);
  }
  len = bufor;
}

//Saves byte to EEPROM
void EpromService::SaveByte(int startAt, byte val)
{
  EEPROM.write(startAt, val);
  EEPROM.commit();
}

//Reads byte from EEPROM
byte EpromService::ReadByte(byte startAt)
{
  byte Read = -1;
  Read = EEPROM.read(startAt);
  return Read;
}