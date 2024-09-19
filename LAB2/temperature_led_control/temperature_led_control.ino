#include <Adafruit_Sensor.h>
#include <DHT.h>

// Define sensor and relay pins
#define DHTPIN 16
#define DHTTYPE DHT22
#define LIGHT_SENSOR_ANAPIN 4
#define RELAY_PIN 21

DHT dht(DHTPIN, DHTTYPE);

// Timer variables
unsigned long previousMillis = 0;  // Stores the last time temperature was updated
const long interval = 5000;        // Interval at which to read temperature (5 seconds)

// Calibration offset (adjust this value based on your calibration)
float temperatureOffset = 1.0;  // Example: sensor reads 2°C higher than actual

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();  // Current time

  // Read the light sensor and control the relay (respond immediately)
  int lightValue = analogRead(LIGHT_SENSOR_ANAPIN);

  // Immediately control relay based on light conditions
  if (lightValue < 300) {
    digitalWrite(RELAY_PIN, HIGH);  // Turn on relay if low light detected
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Turn off relay if high light detected
  }

  // Read humidity, temperature, and light values every 5 seconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature()+ temperatureOffset ;

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println(F("Failed to read from DHT sensor!"));
    } else {
      float heatIndex = dht.computeHeatIndex(temperature, humidity, false);
      // Update the sensor data
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.print(" %\t Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");
    }

    // Print the light sensor values every 5 seconds
    Serial.print("Analog Light Value: ");
    Serial.println(lightValue);
  }

  // Check for request to display temperature on demand
  if (Serial.available() > 0) {
    String request = Serial.readString();
    request.trim();  // Remove any extra spaces or newline characters
    if (request == "temperature") {
      float temperature = dht.readTemperature() + temperatureOffset;
      Serial.print(F("Current Temperature: "));
      Serial.print(temperature);
      Serial.println(F("°C"));
    }
  }

}
