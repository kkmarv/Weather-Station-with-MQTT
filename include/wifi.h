bool connectToWifi();
bool connectToMQTT();
void publishMessage(const char*, const char*);
void publishMessagePeriodically(const char*, const char*, unsigned long);
