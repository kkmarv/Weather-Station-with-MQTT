#include <Arduino.h>
#include <MQUnifiedsensor.h>

#include <map>
#include <string>

#include "sensors.hpp"
#include "utils.hpp"

#define BOARD "ESP8266"
#define SENSOR_TYPE "MQ-135"
#define VOLTAGE_RESOLUTION 5
#define ADC_BIT_RESOLUTION 10      // For arduino UNO/MEGA/NANO
#define RATIO_MQ135_CLEAN_AIR 3.6  // RS / R0 = 3.6 ppm

/**
 * @param pin The gas sensor's analog pin.
 */
GasSensor::GasSensor(uint8_t pin) : mq_(BOARD, VOLTAGE_RESOLUTION, ADC_BIT_RESOLUTION, pin, SENSOR_TYPE) {
  // Set math model to calculate the PPM concentration and the value of constants
  mq_.setRegressionMethod(1);  //_PPM =  a*ratio^b
  mq_.init();
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
  LOG("Air quality sensor calibrating. Please wait.");
  float calcR0 = 0;

  for (int i = 1; i <= 10; i++) {
    mq_.update();
    calcR0 += mq_.calibrate(RATIO_MQ135_CLEAN_AIR);
    LOG(".");
  }
  mq_.setR0(calcR0 / 10);
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
  mq_.setA(605.18);
  mq_.setB(-3.937);
  return mq_.readSensor();
}

float GasSensor::readEthanol() {
  mq_.setA(77.255);
  mq_.setB(-3.18);
  return mq_.readSensor();
}

float GasSensor::readCarbonDioxide() {
  mq_.setA(110.47);
  mq_.setB(-2.862);
  return mq_.readSensor();
}

float GasSensor::readToluene() {
  mq_.setA(44.947);
  mq_.setB(-3.445);
  return mq_.readSensor();
}

float GasSensor::readAmmonium() {
  mq_.setA(102.2);
  mq_.setB(-2.473);
  return mq_.readSensor();
}

float GasSensor::readAcetone() {
  mq_.setA(34.668);
  mq_.setB(-3.369);
  return mq_.readSensor();
}

const std::map<String, float>& GasSensor::read() {
  mq_.update();

  readings_["CO"] = readCarbonMonoxide();
  readings_["C2H6O"] = readEthanol();
  readings_["CO2"] = readCarbonDioxide();
  readings_["C7H8"] = readToluene();
  readings_["NH4"] = readAmmonium();
  readings_["C3H6O"] = readAcetone();

  LOG_LN("Acetone: " + String(readings_["C3H60"]) + " ppm");
  LOG_LN("Ammonium: " + String(readings_["NH4"]) + " ppm");
  LOG_LN("Carbonmonoxide: " + String(readings_["CO"]) + " ppm");
  LOG_LN("Carbondioxide: " + String(readings_["CO2"]) + " ppm");
  LOG_LN("Ethanol: " + String(readings_["C2H60"]) + " ppm");
  LOG_LN("Toluene: " + String(readings_["C7H8"]) + " ppm");

  return readings_;
}