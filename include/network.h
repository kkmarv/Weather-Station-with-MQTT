// WIFI
void connectToWifi();

// MQTT
void connectToMQTT(unsigned long keepAliveInterval);
void sendMessage(const String& topic, const String& message, short qos = 0);
void sendMessagePeriodically(unsigned long interval, const String& topic, const String& message, short qos = 0);
