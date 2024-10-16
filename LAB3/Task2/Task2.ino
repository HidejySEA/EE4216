#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32Server";
const char* password = "12345678";
const char* serverURL = "http://192.168.4.1";   // Base URL
int matricNumber = 239631; // Replace this with your actual matric number

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  
  Serial.println("Connected to Wi-Fi");

  // First HTTP request
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    int httpCode = http.GET();
    
    if(httpCode > 0) {
      String payload = http.getString();
      Serial.println("HTTP Response: " + payload);

      // Get the last digit of the matric number and perform modulo 3
      int lastDigit = matricNumber % 10;
      int k = lastDigit % 3;
      
      // Perform the second GET request by converting serverURL to String and concatenate
      String endpoint = String(serverURL) + "/" + String(k);
      Serial.println("Fetching from endpoint: " + endpoint);
      
      http.begin(endpoint);
      int secondHttpCode = http.GET();
      
      if(secondHttpCode > 0) {
        String secondPayload = http.getString();
        Serial.println("Second HTTP Response: " + secondPayload);
      } else {
        Serial.println("Error in second HTTP request");
      }

    } else {
      Serial.println("Error in first HTTP request");
    }
    
    http.end(); // Close connection
  }
}

void loop() {
  // No continuous tasks in the loop
}
