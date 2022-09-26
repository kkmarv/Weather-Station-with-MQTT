#include <Arduino.h>
#include <DHT.h>

#include "network.hpp"
#include "sensors.hpp"

// Interval in microseconds how often a message should be sent via MQTT.
const unsigned int messageInterval = 10000;
// The milliseconds passed since last call to haveMillisPassed() happened.
unsigned long millisSinceLastCheck = 0;

// Sensors
HumidityTemperatureSensor humidityTemperatureSensor;
LightSensor lightSensor;

// Returns if the specified interval has passed since the last call to this function.
bool haveMillisPassed(unsigned long passedMillis) {
  const unsigned long millisNow = millis();

  if (millisNow - millisSinceLastCheck >= passedMillis) {
    millisSinceLastCheck = millisNow;
    return true;
  }
  return false;
}

void setup() {
  SETUP_SERIAL(9600);

  connectToWifi();
  connectToMQTT(messageInterval * 2);
}

void loop() {
  if (haveMillisPassed(messageInterval)) {
    String payload = "{temperature: \"" + String(humidityTemperatureSensor.readTemperature()) + "\", humidity: \"" +
                     String(humidityTemperatureSensor.readHumidity()) + "\", ambientLight: \"" +
                     String(lightSensor.read()) + "\"}";

    sendMQTTMessage("test", payload);
  }
}
