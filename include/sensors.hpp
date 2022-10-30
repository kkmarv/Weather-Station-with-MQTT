#pragma once

#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <DHT.h>
#include <MQUnifiedsensor.h>
#include <map>

#include "debug.hpp"

// Represents a temperature/humidity sensor from the DHT series.
class HumidityTemperatureSensor {
 private:
  DHT dht_;

 public:
  /**
   * @param pin The sensor's digital read/write pin.
   * @param dhtType The type of the DHT. Possible values are: "DHT11", "DHT12", "DHT21" "DHT22"
   */
  HumidityTemperatureSensor(uint8_t pin, uint8_t dhtType);

  /**
   * Read and return temperature.
   * @return Temperature in °C.
   */
  float readTemperature();

  /**
   * Read and return relative humidity.
   * @return Relative humidity in percent (1-100%).
   */
  float readHumidity();
};

// Represents any BH1750 light sensor.
class LightSensor {
 private:
  BH1750 bh_;
  uint8_t sdaPin_, sclPin_;

 public:
  /**
   * @param sdaPin The light sensor's SDA pin.
   * @param sclPin The light sensor's SCL pin.
   */
  LightSensor(uint8_t sdaPin, uint8_t sclPin);

  /**
   *
   */
  void init();

  /**
   * Read and return ambient light intensity.
   * @return Light intensity in lux (lx).
   */
  float read();
};

// Represents the BMP280 pressure/temperature sensor.
class PressureTemperatureSensor {
 private:
  Adafruit_BMP280 bmp_;
  unsigned long lastReadTimestamp_ = 0;
  unsigned long readRefreshInterval_;

 public:
  /**
   * @param readRefreshInterval
   */
  PressureTemperatureSensor(unsigned long readRefreshInterval);
  void init();

  /**
   * Read and return the barometric pressure.
   * @return Barometric pressure in hPa.
   */
  float readPressure();

  /**
   * Read and return the temperature.
   * @return Temperature in °C.
   */
  float readTemperature();
};

class WetnessSensor {
 private:
  uint8_t pin_, controlPin_;

 public:
  /**
   * @param pin The wetness sensor's analog read pin.
   * @param controlPin The wetness sensor's digital write pin.
   * If set to HIGH, The wetness sensor's readings will be written to the analog pin. (This will be handled internally.)
   * This is used because the Wemos D1 only has one analog pin available.
   */
  WetnessSensor(uint8_t pin, uint8_t controlPin);

  /**
   * Read and return the sensor's wetness.
   * @return Wetness from 0 (dry) to 1 (wet). Note: The sensor isn't very accurate and ranges between 0.09 and 0.7.
   */
  float read();
};

// Represents the MQ-135 gas sensor.
class GasSensor {
 private:
  MQUnifiedsensor mq_;
  uint8_t controlPin_;
  std::map<String, float> readings_ = {
      {"CO", -1.0f},     // carbonMonoxide
      {"C2H6O", -1.0f},  // alcohol aka ethanol
      {"CO2", -1.0f},    // carbonDioxide
      {"C7H8", -1.0f},   // toluene
      {"NH4", -1.0f},    // ammonium
      {"C3H6O", -1.0f}   // acetone
  };

 public:
  /**
   * @param pin The gas sensor's analog pin.
   * @param controlPin The gas sensor's digital write pin.
   * If set to HIGH, The gas sensor's readings will be written to the analog pin. (This will be handled internally.)
   * This is used because the Wemos D1 only has one analog pin available.
   */
  GasSensor(uint8_t pin, uint8_t controlPin);

  /**
   * MQ Calibration
   *
   * In this routine the sensor will measure the resistance of the sensor supposedly before being pre-heated
   * and on clean air (Calibration conditions), setting up R0 value.
   * We recommend executing this routine only on setup in laboratory conditions.
   * This routine does not need to be executed on each restart, you can load your R0 value from eeprom.
   */
  void init();

  /**
   * @return
   */
  const std::map<String, float>& read();

  float readAcetone();
  float readAmmonium();
  float readCarbonDioxide();
  float readCarbonMonoxide();
  float readEthanol();
  float readToluene();
};

// Represents a custom 3D printed anemometer.
class WindSensor {
 public:
  enum WindDirection { NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST };

 private:
  uint8_t speedPin_, northPin_, eastPin_, southPin_, westPin_;
  int anemometerRadius_;             // in mm from middle to magnet
  int anemometerRotationCount_ = 0;  // number of full rotations until the last call to calculateSpeed()
  WindDirection windDir_ = NORTH;    // the last wind direction that has been read from the sensor
  bool lastAnemometerSignal_ = false;
  unsigned long calculationInterval_;

 public:
  /**
   * @param anemometerRadius The radius of the anemometer in millimeters.
   * Please specify the radius only up to the magnet.
   * @param calculationInterval The interval in milliseconds in which the wind speed will be calculated.
   * @param speedPin Will be used to calculate wind speed.
   * Is set to HIGH if the anemometer does a full rotation and passes a reed switch.
   * @param northPin Indicates with a HIGH that the wind direction is approximately North.
   * @param eastPin Indicates with a HIGH that the wind direction is approximately East.
   * @param southPin Indicates with a HIGH that the wind direction is approximately South.
   * @param westPin Indicates with a HIGH that the wind direction is approximately West.
   */
  WindSensor(int anemometerRadius,
             unsigned long calculationInterval,
             uint8_t speedPin,
             uint8_t northPin,
             uint8_t eastPin,
             uint8_t southPin,
             uint8_t westPin);

  /**
   * Read and return the current wind direction.
   * @returns The wind direction as celestial direction.
   */
  WindDirection readDirection();

  /**
   * Calculate and return the average wind speed over the given interval.
   * Remember to call checkOnFullRotation() inside main loop.
   * @returns Wind speed in km/h.
   */
  float calculateSpeed();

  /**
   * Reads the windSpeed pin and checks if the anemometer did a full rotation yet,
   * then updates the internal WindSensor state.
   */
  void checkOnFullRotation();

  /**
   *
   */
  String getString(WindSensor::WindDirection direction);
};
