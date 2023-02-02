#include "analog_sensor.h"
#include <iostream>
#include <Arduino.h>
#include <math.h>

using namespace std;

AnalogSensor::AnalogSensor(int pin) {
  this->pin = pin;
}
int AnalogSensor::readSensor() { //lê sensor analógico, dá uma leitura entre 0 e 255 se lê algo
  this->raw_reading = analogRead(this->pin);
  //Serial.println("estou em analog_sensor, funcao readSensor");
  //Serial.println(raw_reading);
  if (raw_reading >= 0 && raw_reading <= 4095)
    return (int)((4095.0- (float)this->raw_reading)*(float)ANALOG_TO_CM); //conta do billy para converter (perguntar)
  else
    return -1; // sensor com problema 
}
int AnalogSensor::filterSensor(){ // tentando colocar o filtro do codigo antigo, tentando e falhando
  // mea = this->raw_reading; ?
   _kalman_gain = _err_estimate/(_err_estimate + _err_measure);
  _current_estimate = _last_estimate + _kalman_gain * (mea - _last_estimate); //mea: quanto que o sensor pode variar (ver isso)
  _err_estimate =  (1.0 - _kalman_gain)*_err_estimate + fabs(_last_estimate-_current_estimate)*_q;
  _last_estimate=_current_estimate;

  return _current_estimate;
  
}
  
  
