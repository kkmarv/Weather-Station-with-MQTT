#include <Arduino.h>
#include <MQUnifiedsensor.h>

#include <map>
#include <string>

#include "utils.hpp"
#include "sensors.hpp"

#define board "ESP8266"
#define Voltage_Resolution 5
#define GASPIN A0
#define type "MQ-135"
#define ADC_Bit_Resolution 10   // For arduino UNO/MEGA/NANO
#define RatioMQ135CleanAir 3.6  // RS / R0 = 3.6 ppm

GasSensor::GasSensor() : _mq(board, Voltage_Resolution, ADC_Bit_Resolution, GASPIN, type) {
  // Set math model to calculate the PPM concentration and the value of constants
  _mq.setRegressionMethod(1);  //_PPM =  a*ratio^b
  _mq.init();
  /*
    //If the RL value is different from 10K please assign your RL value with the following method:
    _mq.setRL(10);
  */
  /*****************************  MQ CAlibration ********************************************/
  // Explanation:
  // In this routine the sensor will measure the resistance of the sensor supposedly before being pre-heated
  // and on clean air (Calibration conditions), setting up R0 value.
  // We recomend executing this routine only on setup in laboratory conditions.
  // This routine does not need to be executed on each restart, you can load your R0 value from eeprom.
  LOG("MQ5 Calibrating. Please wait.");
  float calcR0 = 0;

  for (int i = 1; i <= 10; i++) {
    _mq.update();
    calcR0 += _mq.calibrate(RatioMQ135CleanAir);
    LOG(".");
  }
  _mq.setR0(calcR0 / 10);
  LOG("  done!.");

  if (isinf(calcR0)) {
    LOG_LN("Warning: Connection issue. R0 is infinite (Open circuit detected) please check your wiring and supply");
    blinkForever(1000);
  } else if (calcR0 == 0) {
    LOG_LN("Warning: Connection issue. R0 is zero (Analog pin shorts to ground) please check your wiring and supply");
    blinkForever(1000);
  }

  LOG_LN("Waiting for readings...");
}

float GasSensor::readCarbonMonoxide() {
  _mq.setA(605.18);
  _mq.setB(-3.937);
  return _mq.readSensor();
}

float GasSensor::readEthanol() {
  _mq.setA(77.255);
  _mq.setB(-3.18);
  return _mq.readSensor();
}

float GasSensor::readCarbonDioxide() {
  _mq.setA(110.47);
  _mq.setB(-2.862);
  return _mq.readSensor();
}

float GasSensor::readToluene() {
  _mq.setA(44.947);
  _mq.setB(-3.445);
  return _mq.readSensor();
}

float GasSensor::readAmmonium() {
  _mq.setA(102.2);
  _mq.setB(-2.473);
  return _mq.readSensor();
}

float GasSensor::readAcetone() {
  _mq.setA(34.668);
  _mq.setB(-3.369);
  return _mq.readSensor();
}

std::map<String, float> GasSensor::read() {
  _mq.update();

  std::map<String, float> gasReadings = {
      {"CO", readCarbonMonoxide()},  // carbonMonoxide
      {"C2H6O", readEthanol()},      // alcohol aka ethanol
      {"CO2", readCarbonDioxide()},  // carbonDioxide
      {"C7H8", readToluene()},       // toluene
      {"NH4", readAmmonium()},       // ammonium
      {"C3H6O", readAcetone()}       // acetone
  };

  LOG_LN("Acetone: " + String(gasReadings["C3H60"]) + " ppm");
  LOG_LN("Ammonium: " + String(gasReadings["NH4"]) + " ppm");
  LOG_LN("Carbonmonoxide: " + String(gasReadings["CO"]) + " ppm");
  LOG_LN("Carbondioxide: " + String(gasReadings["CO2"]) + " ppm");
  LOG_LN("Ethanol: " + String(gasReadings["C2H60"]) + " ppm");
  LOG_LN("Toluene: " + String(gasReadings["C7H8"]) + " ppm");
  return gasReadings;
}