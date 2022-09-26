#pragma once

#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>

#include "debug.hpp"

// WIFI
void connectToWifi();

// MQTT
void connectToMQTT(unsigned long keepAliveInterval);
void sendMessage(const String& topic, const String& message, short qos = 0);
void sendMessagePeriodically(unsigned long interval, const String& topic, const String& message, short qos = 0);
void sendMessagePeriodically(unsigned long interval, const String& topic, String (*toJSON)(), short qos = 0);
