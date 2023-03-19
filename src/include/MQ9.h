#ifndef mq9_h
#define mq9_h
#include "Arduino.h"


class MQ9 {
public:
    MQ9(int pin, float r0);
    void updateMesurements();
    float getRatio();
    int getSensorValue();
    float getSensorVolt();
    int getPpm();
private:
    float sensor_value;
    float measured_volt;
    float RS_gas;
    float ratio;
    int ppm;
    float R0;
    int pin;
};
#endif