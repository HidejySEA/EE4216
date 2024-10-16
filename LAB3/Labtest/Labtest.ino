#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32Server3";  
const char* password = "12345678";  
const char* serverURL = "http://192.168.4.1";  // Webserver IP

void setup() {
  Serial.begin(115200);

  // Connect to the Wi-Fi Access Point (AP)
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  
  // Wait until the ESP32 is connected to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to Wi-Fi");

  // Print the IP address assigned to the ESP32
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Make sure the connection is active
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Send an HTTP GET request to the root of the web server
    http.begin(serverURL);
    int httpCode = http.GET();
    
    // Check the response code
    if(httpCode > 0) {
      String payload = http.getString();
      Serial.println("HTTP Response: " + payload);

      // The server asks for a POST request to "/secret"
      String secretEndpoint = String(serverURL) + "/secret";  
      Serial.println("Sending POST request to: " + secretEndpoint);
      
      http.begin(secretEndpoint);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");  
      
      // Send the POST request
      int postHttpCode = http.POST("");  
      
      if(postHttpCode > 0) {
        String secretMessage = http.getString();
        Serial.println("Secret Message: " + secretMessage);
      } else {
        Serial.println("Error in POST request to /secret");
      }

    } else {
      Serial.println("Error in HTTP request to the root");
    }

    http.end();  
  } else {
    Serial.println("Wi-Fi connection failed");
  }
}

void loop() {
  
}