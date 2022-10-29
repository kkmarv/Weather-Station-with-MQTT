#include <Arduino.h>
#include <ArduinoJson.h>
#include <DHT.h>

#include "network.hpp"
#include "sensors.hpp"
#include "utils.hpp"

// Interval in microseconds how often to read sensors and send data via MQTT.
const unsigned int messageInterval = 10000;

// Sensors
GasSensor gasSensor(A0, D6);
RainSensor rainSensor(A0, D7);
LightSensor lightSensor(D14, D15);
// Use pin D9 for the wind speed sensor to have the onboard SCL LED light up when there is a HIGH signal on D9.
WindSensor windSensor(D9, D6, D4, D3, D5);
HumidityTemperatureSensor humidityTemperatureSensor(D13, DHT22);
// Unfortunately, we have no functioning BMP280 at the moment.
// PressureTemperatureSensor pressureTemperatureSensor(messageInterval);

void setup() {
  SETUP_SERIAL(9600);
  // Used to flash the internal LED when doing sensor readings.
  // Remove this and the latter line when using pin D5 elsewhere or this will set LOW on D5.
  pinMode(LED_BUILTIN, OUTPUT);

  // connectToWifi();
  // connectToMQTT(messageInterval * 2);
}

void loop() {
  // continuous readings
  // windSensor.readSpeed();

  // one time readings
  if (haveMillisPassed(messageInterval)) {
    digitalWrite(LED_BUILTIN, LOW);

    // Construct a JSON message.
    StaticJsonDocument<200> payload;  // TODO optimize byte size to actual size of JSON contents
    payload["temperature"] = String(humidityTemperatureSensor.readTemperature());
    payload["humidity"] = String(humidityTemperatureSensor.readHumidity());
    // payload["pressure"] = String(pressureTemperatureSensor.readPressure());
    payload["rain"] = String(rainSensor.read());
    // payload["windSpeed"] = String();
    payload["windDirection"] = String(windSensor.readDirection());
    payload["lightIntensity"] = String(lightSensor.read());
    auto& gasReadings = gasSensor.read();
    payload["airQuality"]["acetone"] = gasReadings.at("C3H6O");
    payload["airQuality"]["ammonium"] = gasReadings.at("NH4");
    payload["airQuality"]["carbonDioxide"] = gasReadings.at("CO2");
    payload["airQuality"]["carbonMonoxide"] = gasReadings.at("CO");
    payload["airQuality"]["ethanol"] = gasReadings.at("C2H6O");
    payload["airQuality"]["toluene"] = gasReadings.at("C7H8");

    // sendMQTTMessage("weather", payload);

    digitalWrite(LED_BUILTIN, HIGH);
    LOG_LN();
  }
}
