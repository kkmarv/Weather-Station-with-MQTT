#include <Arduino.h>
#include <MQUnifiedsensor.h>

#include <map>
#include <string>

#include "sensors.hpp"
#include "utils.hpp"

#define GAS_PIN A0
#define BOARD "ESP8266"
#define SENSOR_TYPE "MQ-135"
#define VOLTAGE_RESOLUTION 5
#define ADC_BIT_RESOLUTION 10      // For arduino UNO/MEGA/NANO
#define RATIO_MQ135_CLEAN_AIR 3.6  // RS / R0 = 3.6 ppm

GasSensor::GasSensor() : _mq(BOARD, VOLTAGE_RESOLUTION, ADC_BIT_RESOLUTION, GAS_PIN, SENSOR_TYPE) {
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
    calcR0 += _mq.calibrate(RATIO_MQ135_CLEAN_AIR);
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

const std::map<String, float>& GasSensor::read() {
  _mq.update();

  _readings["CO"] = readCarbonMonoxide();
  _readings["C2H6O"] = readEthanol();
  _readings["CO2"] = readCarbonDioxide();
  _readings["C7H8"] = readToluene();
  _readings["NH4"] = readAmmonium();
  _readings["C3H6O"] = readAcetone();

  LOG_LN("Acetone: " + String(_readings["C3H60"]) + " ppm");
  LOG_LN("Ammonium: " + String(_readings["NH4"]) + " ppm");
  LOG_LN("Carbonmonoxide: " + String(_readings["CO"]) + " ppm");
  LOG_LN("Carbondioxide: " + String(_readings["CO2"]) + " ppm");
  LOG_LN("Ethanol: " + String(_readings["C2H60"]) + " ppm");
  LOG_LN("Toluene: " + String(_readings["C7H8"]) + " ppm");

  return _readings;
}