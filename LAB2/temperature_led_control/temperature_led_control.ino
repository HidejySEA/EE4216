#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Define sensor and relay pins
#define DHTPIN 4
#define DHTTYPE DHT22
#define LIGHT_SENSOR_PIN 34
#define RELAY_PIN 14

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Update the sensor data every 5 seconds
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C"));

  // Read the light sensor and control the relay
  int lightValue = analogRead(LIGHT_SENSOR_PIN);
  if (lightValue < 500) {
    digitalWrite(RELAY_PIN, HIGH);  // Turn on LED
    Serial.println("Relay ON: Low light detected");
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Turn off LED
    Serial.println("Relay OFF: High light detected");
  }

  // Check for request to display temperature on demand
  if (Serial.available() > 0) {
    String request = Serial.readString();
    request.trim();  // Remove any extra spaces or newline characters
    if (request == "temperature") {
      Serial.print(F("Current Temperature: "));
      Serial.print(temperature);
      Serial.println(F("°C"));
    }
  }

  delay(5000);  // Delay 5 seconds before repeating
}
