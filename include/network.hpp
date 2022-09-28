#pragma once

#include <ArduinoJson.h>

#include "debug.hpp"

// WIFI

// Connect to a Wifi AP.
// Blocks program as long as a connection cannot be established.
void connectToWifi();

// MQTT

// Connect to a MQTT Broker.
// Blocks program as long as a connection cannot be established.
void connectToMQTT(unsigned long keepAliveInterval);
// Send a message to a MQTT topic.
void sendMQTTMessage(const String& topic, const String& payload, short qos = 0);
// Send a JSON message to a MQTT topic.
void sendMQTTMessage(const String& topic, StaticJsonDocument<200> jsonDoc, short qos = 0);
