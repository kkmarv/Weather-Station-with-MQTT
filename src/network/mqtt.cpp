#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>
#include <StreamUtils.h>

#include "network.hpp"

const String userName = MQTT_USER;
const String userPass = MQTT_PASS;
const String broker = MQTT_BROK;
const unsigned short port = MQTT_PORT;

WiFiClient wifiClient;              // The client used to access other hosts
MqttClient mqttClient(wifiClient);  // The client used to connect to a MQTT Broker

unsigned long _keepAliveInterval;  // TODO underscore or not?

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

void sendMQTTMessage(const String& topic, const String& payload, short qos) {
  if (!mqttClient.connected()) {
    LOG_LN("Connection to MQTT Broker lost!");
    connectToMQTT();
  } else {  // Only send message when connected to prevent sending old sensor data.
    mqttClient.beginMessage(topic, false, qos, false);
    mqttClient.print(payload);
    mqttClient.endMessage();

    LOG_LN("Sent message (QoS " + String(qos) + "): " + payload);
  }
}

void sendMQTTMessage(const String& topic, StaticJsonDocument<200> jsonDoc, short qos) {
  String payload;
  serializeJson(jsonDoc, payload);
  sendMQTTMessage(topic, payload, qos);
}
