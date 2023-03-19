#include <Arduino.h>
#include "include/MQ9.h"


MQ9::MQ9(int pin, float r0){
    this->pin = pin;
    this->R0 = r0;
}

void MQ9::updateMesurements(){
  sensor_value = 0;
  for (int x = 0 ; x < 100 ; x++) {
    sensor_value = sensor_value + analogRead(pin);
    delay(10);
  }
  sensor_value = sensor_value / 100.0;
  measured_volt = sensor_value / 1024 * 3.3;
  RS_gas = (5.0 - measured_volt) / measured_volt;
  ratio = RS_gas / R0;
  if ( ratio < 2 ) {
    // přepočet načtených dat, z rozsahu 0-700
    // na koncentraci 200-10000
    ppm = map(ratio*100, 150, 79, 200, 1000);
  }else{
    ppm=0;
  }
};



float MQ9::getRatio(){
    return ratio;
};
int MQ9::getSensorValue(){
    return sensor_value;
};
float MQ9::getSensorVolt(){
    return measured_volt;
};
int MQ9::getPpm(){
    return ppm;
};