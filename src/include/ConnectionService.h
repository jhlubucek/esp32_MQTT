
#ifndef ConnecitionService_h
#define ConnecitionService_h
#include "Arduino.h"
#include "include/EpromService.h"

class ConnectionService {
public:
    ConnectionService();
    void loadFromEprom();
    void reconnectWifi();
    void reconnectMqtt();
    void setupThroughSerial();
    void start();
    void publishData(const char* topic, const char* payload);
private:
    int err = 0; //wifi:1  MQTT:2
    int led = 2;
    char ssid[40];
    char pass[40];
    char userHash[40];
    char planterName[40];
    EpromService epromService;
    const char* mqtt_user;
    const char* mqtt_password;
    const char* mqtt_server;
};
#endif



