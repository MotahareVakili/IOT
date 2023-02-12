#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "0987654321";
const char* password = "1234567890";

ESP8266WebServer server(80);

int relayPin = 5; // pin to connect the relay

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP8266 Oven Control</h1>";
  html += "<form method='get' action='/on'>";
  html += "<input type='submit' value='ON'>";
  html += "</form>";
  html += "<form method='get' action='/off'>";
  html += "<input type='submit' value='OFF'>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  
  digitalWrite(relayPin, LOW);
  String html = "<html><body>";
  html += "<h1>ESP8266 Oven Control</h1>";
  html += "<p>Oven is currently ON</p>";
  html += "<form method='get' action='/'>";
  html += "<input type='submit' value='Back to Main'>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOff() {
  digitalWrite(relayPin, HIGH);
  String html = "<html><body>";
  html += "<h1>ESP8266 Oven Control</h1>";
  html += "<p>Oven is currently OFF</p>";
  html += "<form method='get' action='/'>";
  html += "<input type='submit' value='Back to Main'>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}
