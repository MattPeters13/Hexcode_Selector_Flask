#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
 // Optional, for parsing JSON if needed

// Replace with your network credentials
const char* ssid = "MojoDojoCasaHouse";
const char* password = "H3LL0barbi3100$";

// Define the web server on port 80
WiFiServer server(80);

String receivedHexCode = ""; // Variable to store the received hex code

void setup() {
  // Start the serial communication
  Serial.begin(9600);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client connected");

    // Wait for data from client
    while (client.connected() && !client.available()) {
      delay(1);
    }

    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println("Request: " + request);
    client.read(); // Read the newline character after the request

    // Check if this is a POST request
    if (request.indexOf("POST") >= 0) {
      // Skip HTTP headers to reach the payload
      while (client.available()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") {
          break; // Empty line indicates end of headers
        }
      }

      // Read the payload (hex string)
      if (client.available()) {
        receivedHexCode = client.readStringUntil('\r'); // Read the hex string
        Serial.println("Received Hex Code: " + receivedHexCode);
      }
    }

    // Send response to client
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<html><body><h1>Hex code received!</h1></body></html>");

    // Close the connection
    delay(3);
    client.stop();
    Serial.println("Client disconnected");
  }
}