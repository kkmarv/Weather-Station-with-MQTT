#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN D4      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // Sensortype DHT 11

DHT dht(DHTPIN, DHTTYPE);

void dhtSetup() {
  Serial.begin(9600);
  dht.begin();
}

void readDHT() {
  // Wait a few seconds between measurements
  // because the sensor's readings may take up to 2 seconds (its a very slow sensor)
  delay(2000);

  float h = dht.readHumidity();      // Reading temperature or humidity takes about 250 milliseconds
  float tc = dht.readTemperature();  // Read temperature as Celsius (the default)

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(tc)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hic = dht.computeHeatIndex(tc, h, false);  // Compute heat index in Celsius (isFahrenheit = false)

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(tc);
  Serial.print("°C / ");
  Serial.print(hic);
  Serial.println("°C");
}
