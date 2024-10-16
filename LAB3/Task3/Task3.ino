#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHTPIN 6           // Pin connected to DHT22 sensor
#define DHTTYPE DHT11      // DHT22 sensor type
#define LED_PIN 16         // Onboard LED pin

const char* ssid = "notyouriphone";
const char* password = "hidejy123";

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void handleRoot() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  
  String html = "<h1>ESP32 Web Server</h1>";
  html += "<p>Temperature: " + String(temp) + " °C</p>";
  html += "<p>Humidity: " + String(hum) + " %</p>";
  html += "<a href=\"/LED_ON\">Turn LED ON</a><br>";
  html += "<a href=\"/LED_OFF\">Turn LED OFF</a><br>";
  
  server.send(200, "text/html", html);
}

void handleLEDOn() {
  digitalWrite(LED_PIN, HIGH);
  server.send(200, "text/html", "LED is ON");
}

void handleLEDOff() {
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/html", "LED is OFF");
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(LED_PIN, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");
  Serial.println(WiFi.localIP());

  // Start Web Server
  server.on("/", handleRoot);
  server.on("/LED_ON", handleLEDOn);
  server.on("/LED_OFF", handleLEDOff);
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient(); // Listen for HTTP requests
}
