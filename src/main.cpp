#include <Arduino.h>
#include "include/config.h"
#include "WiFi.h"
#include "PubSubClient.h"
#include "include/ConnectionService.h"
#include "include/MQ9.h"
#include "DHT.h"


char eRead[40];
ConnectionService connectionService;
DHT dht(DHTPIN, DHTTYPE);
char buffer[64];
MQ9 mq9(35, 2.55);




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
  connectionService.connect();

  pinMode (2, OUTPUT);
}
void loop() {
  connectionService.connect();
  digitalWrite(2, HIGH);
  delay(300);
  mq9.updateMesurements();
  int gassensorAnalog = analogRead(MQ2_SENSOR);
  int firesensorAnalog = analogRead(MQ135_SENSOR);
  connectionService.publishData("/jhlubucek/sensor/temp", String(dht.readTemperature()).c_str());
  connectionService.publishData("/jhlubucek/sensor/co2", String(mq9.getPpm()).c_str());
  connectionService.publishData("/jhlubucek/sensor/volt", String(mq9.getSensorVolt()).c_str());
  connectionService.publishData("/jhlubucek/sensor/value", String(mq9.getSensorValue()).c_str());
  connectionService.publishData("/jhlubucek/sensor/ratio", String(mq9.getRatio()).c_str());


  Serial.print("Priblizna koncentrace CO: ");
  Serial.print(mq9.getPpm());
  Serial.println(" ppm.");
  Serial.print("ratio: ");
  Serial.println(mq9.getRatio());
  Serial.print("value: ");
  Serial.println(mq9.getSensorValue());
  Serial.print("volt: ");
  Serial.println(mq9.getSensorVolt());
  Serial.println();

  digitalWrite(2, LOW);
  delay(60000);
}