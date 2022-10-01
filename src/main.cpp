#include <ArduinoJson.h>

#include "network.hpp"
#include "sensors.hpp"
#include "utils.hpp"

// Interval in microseconds how often a message should be sent via MQTT.
const unsigned int messageInterval = 10000;

// Sensors
HumidityTemperatureSensor humidityTemperatureSensor;
LightSensor lightSensor;

void setup() {
  SETUP_SERIAL(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  connectToWifi();
  connectToMQTT(messageInterval * 2);
}

void loop() {
  if (haveMillisPassed(messageInterval)) {
    digitalWrite(LED_BUILTIN, LOW);
    StaticJsonDocument<200> payload;  // TODO optimize byte size to actual size of JSON contents

    payload["temperature"] = String(humidityTemperatureSensor.readTemperature());
    payload["humidity"] = String(humidityTemperatureSensor.readHumidity());
    payload["ambientLight"] = String(lightSensor.read());

    sendMQTTMessage("test", payload);

    digitalWrite(LED_BUILTIN, HIGH);
    LOG_LN();
  }
}
