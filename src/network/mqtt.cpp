#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>

#include "network.h"

const String userName = MQTT_USER;
const String userPass = MQTT_PASS;
const String broker = MQTT_BROK;
const unsigned short port = MQTT_PORT;

WiFiClient wifiClient;              // The client used to access other hosts
MqttClient mqttClient(wifiClient);  // The client used to connect to MQTT Broker

unsigned long _keepAliveInterval;   // TODO underscore or not?
unsigned long _previousMillis = 0;  // used for calculating intervals

// Connect to a MQTT Broker.
// Blocks program as long as a connection cannot be established.
void connectToMQTT(unsigned long keepAliveInterval) {
  _keepAliveInterval = keepAliveInterval;
  mqttClient.setKeepAliveInterval(keepAliveInterval);  // After which time the Broker will disconnect the Client
  mqttClient.setUsernamePassword(userName, userPass);  // Used for authenticating with the Broker

  LOG_LN("Try connecting to MQTT Broker at: " + broker + ":" + port);

  // Try and to connect to the MQTT Broker.
  while (!mqttClient.connect(broker.c_str(), port)) {
    LOG_MQTT_ERROR_CODE(mqttClient.connectError());
    delay(30000);  // Wait 30 seconds before trying to reconnect.
  }
  LOG_LN("Connection established.");
}

void connectToMQTT() {
  connectToMQTT(_keepAliveInterval);
}

// Send a message to a MQTT topic.
void sendMessage(const String& topic, const String& message, short qos) {
  if (!mqttClient.connected()) {
    LOG_LN("Connection to MQTT Broker lost!");
    connectToMQTT();
  } else {  // Only send message when connected to prevent sending old sensor data.
    mqttClient.beginMessage(topic, false, qos, false);
    mqttClient.print(message);
    mqttClient.endMessage();

    LOG_LN("Sent message (QoS " + String(qos) + "): " + message);
  }
}

// Returns if the specified interval has passed since the last call to this function.
bool _hasIntervalPassed(unsigned long interval) {
  const unsigned long currentMillis = millis();

  if (currentMillis - _previousMillis >= interval) {
    _previousMillis = currentMillis;
    return true;
  }
  return false;
}

// Send a message every other interval.
void sendMessagePeriodically(unsigned long interval, const String& topic, const String& message, short qos) {
  if (_hasIntervalPassed(interval)) {
    sendMessage(topic, message, qos);
  }
}
