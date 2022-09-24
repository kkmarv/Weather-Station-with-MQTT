#include <ESP8266WiFi.h>

#include "debug.hpp"
#include "network.hpp"

const char wifiSsid[] = WIFI_SSID;
const char wifiPass[] = WIFI_PASS;
const char userName[] = MQTT_USER;
const char userPass[] = MQTT_PASS;
const char broker[] = MQTT_BROK;
const int port = MQTT_PORT;

// Connect to a Wifi AP.
// Blocks program as long as a connection cannot be established.
void connectToWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  LOG_LN("WiFi Client settings:");

  LOG_LN("    SSID: " + ssid);
  LOG_LN("    Password: " + pass);

  // Although in the official Arduino documentation it is said otherwise,
  // the hostname has to be set AFTER calling WiFi.begin() to be set correctly.
  LOG("    Hostname: ");
  WiFi.hostname(host);
  LOG_LN(WiFi.hostname());

  LOG("    Auto reconnect: ");
  WiFi.setAutoReconnect(true);
  LOG_LN(WiFi.getAutoReconnect());

  LOG("    Persistent: ");
  LOG_LN(WiFi.getPersistent());

  LOG_LN();
  LOG_LN("Connecting...");
  // Retry connection until Client is connected
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    switch (WiFi.status()) {
      case WL_NO_SSID_AVAIL:   // in case configured SSID cannot be reached
      case WL_CONNECT_FAILED:  // if connection failed due to error not originating from client
      case WL_WRONG_PASSWORD:  // if password is incorrect
        LOG("Error while connecting! Error code: " + String(WiFi.status()) + " -> ");
        LOG_WIFI_STATUS_CODE(WiFi.status());

      default:  // WL_DISCONNECTED or WL_IDLE_STATUS: If client isn't in station mode or between states.
        delay(30000);
        break;
    }
  }
  LOG("Connected. The client IP address is: ");
  LOG_LN(WiFi.localIP());
}
