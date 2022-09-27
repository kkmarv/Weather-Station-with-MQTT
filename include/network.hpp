#pragma once

#include "debug.hpp"

// WIFI
void connectToWifi();

// MQTT
void connectToMQTT(unsigned long keepAliveInterval);
void sendMQTTMessage(const String& topic, const String& message, short qos = 0);
