#include <Arduino.h>
#include "config.h"
#include "WiFi.h"
#include "PubSubClient.h"
#include "include/helper.h"
#include "EEPROM.h"
#include "include/EpromService.h"
#include "include/ConnectionService.h"

int err = 0; //wifi:1  MQTT:2

int led = 2;

char ssid[40];
char pass[40];
char userHash[40];
char planterName[40];

EpromService epromService;
WiFiClient espClient;
PubSubClient client(espClient);

const char* mqtt_user = "........";
const char* mqtt_password = "........";
const char* mqtt_server = "broker.mqtt-dashboard.com";

ConnectionService::ConnectionService()
{
}

void ConnectionService::start(){
    reconnectWifi();
    client.setServer(mqtt_server, 1883);
  //client.setCallback(callback); //set for subscribeing
    reconnectMqtt();
}

//loads preset from eprom
void ConnectionService::loadFromEprom() {
  byte x = epromService.ReadByte(0);
  epromService.ReadString(1, x, ssid);

  x = epromService.ReadByte(41);
  epromService.ReadString(42, x, pass);

  x = epromService.ReadByte(83);
  epromService.ReadString(84, x, planterName);

  x = epromService.ReadByte(125);
  epromService.ReadString(126, x, userHash);
}

void ConnectionService::reconnectWifi() {

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    int counter = 0;
    while (WiFi.status() != WL_CONNECTED && counter < 60) {
      counter++;
      delay(500);
    }
  }

  // update err
  if (WiFi.status() != WL_CONNECTED) {
    err += err == 0 || err == 2 ? 1 : 0;
    Serial.println("WiFi failed");
  } else {
    err -= err == 1 || err == 3 ? 1 : 0;
  }

  randomSeed(micros());
}

//loads values from serial port and saves them to eprom
void ConnectionService::setupThroughSerial() {
  Serial.println();
  Serial.print("Enter your WiFi credentials.\n (do not fill to retain old value)\n");

  Serial.print("SSID: ");
  readSerial(ssid, 40);
  Serial.println(ssid);

  Serial.print("PASSWORD: ");
  readSerial(pass, 40);
  Serial.println(pass);

  byte x;
  if (strlen(ssid)) {
    epromService.SaveByte(0, strlen(ssid));
    epromService.SaveString(1, ssid);
  } else {
    x = epromService.ReadByte(0);
    epromService.ReadString(1, x, ssid);
  }

  if (strlen(pass)) {
    epromService.SaveByte(41, strlen(pass));
    epromService.SaveString(42, pass);
  } else {
    x = epromService.ReadByte(41);
    epromService.ReadString(42, x, pass);
  }

  int counter = 0;

  WiFi.begin(ssid, pass);
  while (counter < 30 && WiFi.status() != WL_CONNECTED) {
    counter++;
    delay(200);
    Serial.print(".");
  }
  Serial.println();
  Serial.println(counter < 30 ? "wifi connected sucessfuly!" : "wifi did NOT connect sucessfuly!!!");
}

void ConnectionService::reconnectMqtt() {

  if (!client.connected())
  {
    int counter = 0;
    String clientId = "ESP8266Client-";
    do {
      counter ++;
      clientId += String(random(0xffff), HEX);
      // Attempt to connect
      if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
        //client.subscribe(waterPumpTopic);
        //subscribe
      } else {
        // Wait 5 seconds before retrying
        delay(5000);
      }
    } while (!client.connected() && counter < 3);
  }

  
  

  if (!client.connected()){
    err += err == 0 || err == 1 ? 2 : 0;
  }else{
    err -= err == 2 || err == 3 ? 2 : 0;
  }
      
}

void ConnectionService::publishData(const char* topic, const char* payload)
{
  client.publish(topic, payload);
}
