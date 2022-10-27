#include <Arduino.h>
#include <ArduinoJson.h>
#include <DHT.h>

#include "network.hpp"
#include "sensors.hpp"
#include "utils.hpp"

// Interval in microseconds how often to read sensors and send data via MQTT.
const unsigned int messageInterval = 500;

// Sensors
// HumidityTemperatureSensor humidityTemperatureSensor(D8, DHT22);
// PressureTemperatureSensor pressureTemperatureSensor(messageInterval);
// LightSensor lightSensor(D14, D15);
// RainSensor rainSensor(); // add missing pin
// GasSensor gasSensor(A0);
WindSensor windSensor(D0, D4, D5, D6, D3);

void setup() {
  SETUP_SERIAL(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // connectToWifi();
  // connectToMQTT(messageInterval * 2);
}

void loop() {
  if (haveMillisPassed(messageInterval)) {
    // Flash the internal LED when doing sensor readings.
    digitalWrite(LED_BUILTIN, LOW);

    LOG_LN(windSensor.readDirection());

    // Construct a JSON message.
    // StaticJsonDocument<200> payload;  // TODO optimize byte size to actual size of JSON contents
    // payload["temperature"] = String(humidityTemperatureSensor.readTemperature());
    // payload["humidity"] = String(humidityTemperatureSensor.readHumidity());
    // payload["pressure"] = String(pressureTemperatureSensor.readPressure());
    // payload["rain"] = String(rainSensor.read());
    // payload["windSpeed"] = String();
    // payload["windDirection"] = String();
    // payload["lightIntensity"] = String(lightSensor.read());
    // auto& gasReadings = gasSensor.read();
    // payload["airQuality"]["acetone"] = gasReadings.at("C3H6O");
    // payload["airQuality"]["ammonium"] = gasReadings.at("NH4");
    // payload["airQuality"]["carbonDioxide"] = gasReadings.at("CO2");
    // payload["airQuality"]["carbonMonoxide"] = gasReadings.at("CO");
    // payload["airQuality"]["ethanol"] = gasReadings.at("C2H6O");
    // payload["airQuality"]["toluene"] = gasReadings.at("C7H8");

    // sendMQTTMessage("weather", payload);

    digitalWrite(LED_BUILTIN, HIGH);
    LOG_LN();
  }
}
