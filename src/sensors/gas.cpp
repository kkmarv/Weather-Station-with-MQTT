#include <Arduino.h>
#include <MQUnifiedsensor.h>

#include <map>
#include <string>

#include "sensors.hpp"
#include "utils.hpp"

#define BOARD "ESP8266"
#define SENSOR_TYPE "MQ-135"
#define VOLTAGE_RESOLUTION 5
#define ADC_BIT_RESOLUTION 10      // For Arduino UNO/MEGA/NANO
#define RATIO_MQ135_CLEAN_AIR 3.6  // RS / R0 = 3.6 ppm

GasSensor::GasSensor(uint8_t pin, uint8_t controlPin)
    : mq_(BOARD, VOLTAGE_RESOLUTION, ADC_BIT_RESOLUTION, pin, SENSOR_TYPE) {
  controlPin_ = controlPin;
  pinMode(controlPin_, OUTPUT);

  // Set math model to calculate the PPM concentration and the value of constants
  mq_.setRegressionMethod(1);  //_PPM =  a*ratio^b
  mq_.init();
}

void GasSensor::init() {
  digitalWrite(controlPin_, HIGH);

  LOG("Air quality sensor calibrating.");
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

  digitalWrite(controlPin_, LOW);
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
  return mq_.readSensor() + 400;  // The CO2 reading is relative to the normal atmospheric CO2 content of around 400ppm.
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
  digitalWrite(controlPin_, HIGH);
  mq_.update();

  readings_["CO"] = readCarbonMonoxide();
  readings_["C2H6O"] = readEthanol();
  readings_["CO2"] = readCarbonDioxide();
  readings_["C7H8"] = readToluene();
  readings_["NH4"] = readAmmonium();
  readings_["C3H6O"] = readAcetone();

  digitalWrite(controlPin_, LOW);

  LOG_LN("Acetone: " + String(readings_["C3H60"]) + " ppm");
  LOG_LN("Ammonium: " + String(readings_["NH4"]) + " ppm");
  LOG_LN("Carbonmonoxide: " + String(readings_["CO"]) + " ppm");
  LOG_LN("Carbondioxide: " + String(readings_["CO2"]) + " ppm");
  LOG_LN("Ethanol: " + String(readings_["C2H60"]) + " ppm");
  LOG_LN("Toluene: " + String(readings_["C7H8"]) + " ppm");

  return readings_;
}