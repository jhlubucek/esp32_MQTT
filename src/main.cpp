#include <Arduino.h>
#include "include/config.h"
#include "WiFi.h"
#include "PubSubClient.h"
#include "include/ConnectionService.h"
#include "DHT.h"


char eRead[40];
ConnectionService connectionService;
DHT dht(DHTPIN, DHTTYPE);
char buffer[64];




void setup() {
  Serial.begin(9600);
  pinMode(MQ2_SENSOR, INPUT);
  pinMode(MQ135_SENSOR, INPUT);

  pinMode(MODE_PIN, INPUT);
  if (false && digitalRead(MODE_PIN) == HIGH)
  {
    pinMode(LED_SETUP, OUTPUT);
    digitalWrite(LED_SETUP, HIGH);

    //wait 10s
    delay(10000);
    connectionService.setupThroughSerial();
    while (true) {
      //wait for restart
      delay(60000);
    }
  }

  connectionService.loadFromEprom();
  connectionService.start();

  pinMode (2, OUTPUT);
}
void loop() {
  digitalWrite(2, LOW);
  delay(5000);
  digitalWrite(2, HIGH);
  delay(1000);
  int gassensorAnalog = analogRead(MQ2_SENSOR);
  int firesensorAnalog = analogRead(MQ135_SENSOR);
  connectionService.publishData("/jhlubucek/sensor/temp", String(dht.readTemperature()).c_str());
  //Serial.println(dht.readTemperature());
  Serial.print("Gas Sensor: ");
  Serial.print(gassensorAnalog);
   Serial.print("Fire Sensor: ");
  Serial.print(firesensorAnalog);
  connectionService.publishData("/jhlubucek/sensor/gass", String(gassensorAnalog).c_str());
  connectionService.publishData("/jhlubucek/sensor/fire", String(firesensorAnalog).c_str());
}