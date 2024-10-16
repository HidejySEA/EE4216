#include <WiFi.h>

const char* ssid = "ESP32Server2";      // Wi-Fi SSID
const char* password = "12345678";     // Wi-Fi Password

void setup() {
  Serial.begin(115200);

  // Start connecting to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  // Wait until connected to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  // When connected, print IP address
  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Keep the connection alive
}
