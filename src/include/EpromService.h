
#ifndef EpromService_h
#define EpromService_h
#include "Arduino.h"
#include "PubSubClient.h"
#include "WiFi.h"

class EpromService {
public:
    EpromService();
    void SaveString(int startAt, const char* id);
    void ReadString(byte startAt, byte bufor, char* eRead);
    void SaveByte(int startAt, byte val);
    byte ReadByte(byte startAt);
private:
    byte len;
    void startEprom();
    WiFiClient espClient;
    PubSubClient client;
};
#endif


