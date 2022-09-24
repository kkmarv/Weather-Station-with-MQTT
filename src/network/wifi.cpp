#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>

#include "config.h"
#include "utils.h"

const char wifiSsid[] = WIFI_SSID;
const char wifiPass[] = WIFI_PASS;
const char userName[] = MQTT_USER;
const char userPass[] = MQTT_PASS;
const char broker[] = MQTT_BROK;
const int port = MQTT_PORT;

const int timeoutInterval = 1800000;  // Set the time interval in which a connection with the Broker will be kept alive

WiFiClient wifiClient;              // The client used to connect to wifi
MqttClient mqttClient(wifiClient);  // The client used to connect to mqtt

// Connect to a Wifi AP.
bool connectToWifi() {
  WiFi.begin(wifiSsid, wifiPass);

  Serial.print("Attempting to connect to network SSID: ");
  Serial.println(WiFi.SSID());

  Serial.print("Connecting..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected. IP address: ");
  Serial.println(WiFi.localIP());

  WiFi.setAutoConnect(true);
  WiFi.persistent(true);
  return true;
}

// Returns a string from a MQTT Error Code specifying
// the reason why a connection could not be established.
const char* getString(int errorCode) {
  switch (errorCode) {
    case -2:
      return "MQTT_CONNECTION_REFUSED";
      break;
    case -1:
      return "MQTT_CONNECTION_TIMEOUT";
      break;
    case 0:
      return "MQTT_SUCCESS";
      break;
    case 1:
      return "MQTT_UNACCEPTABLE_PROTOCOL_VERSION";
      break;
    case 2:
      return "MQTT_IDENTIFIER_REJECTED";
      break;
    case 3:
      return "MQTT_SERVER_UNAVAILABLE";
      break;
    case 4:
      return "MQTT_BAD_USER_NAME_OR_PASSWORD";
      break;
    case 5:
      return "MQTT_NOT_AUTHORIZED";
      break;
    default:
      return "UNKNOWN_ERROR";
      break;
  }
}

// Connect to a MQTT Broker.
bool connectToMQTT() {
  mqttClient.setKeepAliveInterval(timeoutInterval);    // After which time the Broker will disconnect the Client
  mqttClient.setUsernamePassword(userName, userPass);  // Used for authenticating with the Broker

  Serial.print("Try connecting to MQTT Broker at: ");
  Serial.print(broker);
  Serial.print(":");
  Serial.println(port);

  // Try to connect to the MQTT Broker.
  while (!mqttClient.connect(broker, port)) {
    int errorCode = mqttClient.connectError();
    Serial.print("Connection failed! Error code: ");
    Serial.print(errorCode);
    Serial.print(" -> ");
    Serial.println(getString(errorCode));
    Serial.println("Will try again in 30 seconds.");
    delay(30000);  // Wait 30 seconds before trying to reconnect.
  }

  Serial.print("Connection established.");
  Serial.println(broker);

  return true;
}

// Publish a message to an MQTT topic with QoS 0.
void publishMessage(const char* topic, const char* message) {
  mqttClient.beginMessage(topic, message);
  mqttClient.print(message);
  mqttClient.endMessage();
  Serial.print("Published message: ");
  Serial.println(message);
}

// Publish a message every other interval.
void publishMessagePeriodically(const char* topic, const char* message, unsigned long interval) {
  if (hasIntervalPassed(interval)) {
    publishMessage(topic, message);
  }
}

// Send a keep alive signal to the MQTT Broker but only if the timeout interval is half over.
void sendKeepAlive() {
  if (hasIntervalPassed(timeoutInterval / 2)) {
    mqttClient.poll();
  }
}
