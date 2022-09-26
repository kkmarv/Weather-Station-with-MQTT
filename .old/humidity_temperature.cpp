// #include <Adafruit_Sensor.h>
// #include <DHT.h>
// #include <DHT_U.h>

// #include "sensors.hpp"

// #define DHTPIN D4      // Digital pin connected to the DHT sensor
// #define DHTTYPE DHT22  // Sensortype DHT 22

// DHT_Unified dht(DHTPIN, DHTTYPE);

// uint32_t delayMS;

// float heatIndex(float temperature, float percentHumidity, bool isFahrenheit);

// void setupDHT() {
//   Serial.begin(9600);
//   dht.begin();
//   sensor_t sensor;
//   // Set delay between sensor readings based on sensor details.
//   delayMS = sensor.min_delay / 1000;
// }

// String readTemp() {
//   String temp;
//   sensors_event_t event;

//   dht.temperature().getEvent(&event);
//   DHT a(DHTPIN, DHTTYPE);

//   if (isnan(event.temperature)) {
//     temp="error";
//   } else {
//     temp = String(event.temperature) + "°C";
//     temp += ", feels like " + String(heatIndex(event.temperature, event.relative_humidity, false)) + "°C";
//   }
//   return temp;
// }

// String readHum() {
//   String hum;
//   sensors_event_t event;

//   dht.humidity().getEvent(&event);
//   if (isnan(event.relative_humidity)) {
//     hum = "error";
//   } else {
//     hum = String(event.relative_humidity) + "%";
//   }
//   return hum;
// }

// /*!
//  *  @brief  Compute Heat Index
//  *  				Using both Rothfusz and Steadman's equations
//  *					(http://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml)
//  *  @param  temperature
//  *          temperature in selected scale
//  *  @param  percentHumidity
//  *          humidity in percent
//  *  @param  isFahrenheit
//  * 					true if fahrenheit, false if celcius
//  *	@return float heat index
//  */
// float heatIndex(float temperature, float percentHumidity, bool isFahrenheit) {
//   float hi;

//   if (!isFahrenheit)
//     temperature = temperature * 1.8 + 32;

//   hi = 0.5 * (temperature + 61.0 + ((temperature - 68.0) * 1.2) + (percentHumidity * 0.094));

//   if (hi > 79) {
//     hi = -42.379 + 2.04901523 * temperature + 10.14333127 * percentHumidity +
//          -0.22475541 * temperature * percentHumidity + -0.00683783 * pow(temperature, 2) +
//          -0.05481717 * pow(percentHumidity, 2) + 0.00122874 * pow(temperature, 2) * percentHumidity +
//          0.00085282 * temperature * pow(percentHumidity, 2) +
//          -0.00000199 * pow(temperature, 2) * pow(percentHumidity, 2);

//     if ((percentHumidity < 13) && (temperature >= 80.0) && (temperature <= 112.0))
//       hi -= ((13.0 - percentHumidity) * 0.25) * sqrt((17.0 - abs(temperature - 95.0)) * 0.05882);

//     else if ((percentHumidity > 85.0) && (temperature >= 80.0) && (temperature <= 87.0))
//       hi += ((percentHumidity - 85.0) * 0.1) * ((87.0 - temperature) * 0.2);
//   }

//   return isFahrenheit ? hi : (hi - 32) * 0.55555;
// }
