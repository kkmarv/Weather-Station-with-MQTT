#include <Arduino.h>
#include <ArduinoJson.h>
#include <DHT.h>

#include "network.hpp"
#include "sensors.hpp"
#include "utils.hpp"

// Interval in milliseconds how often to read sensors and send data via MQTT.
const unsigned int messageInterval = 20000;

// Sensors
GasSensor gasSensor(A0, D6);
WetnessSensor wetnessSensor(A0, D7);
LightSensor lightSensor(D14, D15);
// Use pin D9 for the wind speed pin to have the onboard SCL LED light up when there is a HIGH signal on D9.
WindSensor windSensor(150, messageInterval, D9, D10, D11, D12, D13);
HumidityTemperatureSensor humidityTemperatureSensor(D8, DHT22);
PressureTemperatureSensor pressureTemperatureSensor(messageInterval);

void setup() {
  SETUP_SERIAL(9600);
  // Used to flash the internal LED when doing sensor readings.
  // Beware that pin LED_BUILTIN is shorted with pin D5 when connecting something to that pin.
  pinMode(LED_BUILTIN, OUTPUT);

  gasSensor.init();
  lightSensor.init();
  // Unfortunately, we do not have a working BMP pressure sensor.
  // pressureTemperatureSensor.init();

  connectToWiFi();
  connectToMQTT(messageInterval * 2);
}

void loop() {
  // continuous readings
  windSensor.checkOnFullRotation();

  // one time readings
  if (haveMillisPassed(messageInterval)) {
    digitalWrite(LED_BUILTIN, LOW);

    // Construct a JSON message.
    StaticJsonDocument<200> payload;  // TODO optimize byte size to actual size of JSON contents
    payload["temperature"] = String(humidityTemperatureSensor.readTemperature());
    payload["humidity"] = String(humidityTemperatureSensor.readHumidity());
    // payload["pressure"] = String(pressureTemperatureSensor.readPressure());
    payload["wetness"] = String(wetnessSensor.read());
    payload["windSpeed"] = String(windSensor.calculateSpeed());
    payload["windDirection"] = String(windSensor.readDirection());
    payload["lightIntensity"] = String(lightSensor.read());
    auto& gasReadings = gasSensor.read();
    payload["gas"]["acetone"] = gasReadings.at("C3H6O");
    payload["gas"]["ammonium"] = gasReadings.at("NH4");
    payload["gas"]["carbonDioxide"] = gasReadings.at("CO2");
    payload["gas"]["carbonMonoxide"] = gasReadings.at("CO");
    payload["gas"]["ethanol"] = gasReadings.at("C2H6O");
    payload["gas"]["toluene"] = gasReadings.at("C7H8");

    sendMQTTMessage("weather", payload);

    digitalWrite(LED_BUILTIN, HIGH);
    LOG_LN();
  }
}
