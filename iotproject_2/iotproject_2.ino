#include <ESP8266WiFi.h>

const char* ssid = "tinamotrah";
const char* password = "1234567890";

WiFiServer server(80);

int ledPin = D4;
bool ledStatus = false;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");    
  }

  Serial.println("Connected to WiFi");

  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}
void loop()
{
  WiFiClient client = server.available();
  if(!client)
    return;
  Serial.println("new client");
  while(!client.available()){
    delay(1);
    }
  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("/LED=ON") != -1) {
    ledStatus = true;
      digitalWrite(ledPin, LOW);
    }
  else if (request.indexOf("/LED=OFF") != -1) {
    ledStatus = false;
    digitalWrite(ledPin, HIGH);
    }
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<body>");
  client.print("Led pin is now: ");
  if(ledStatus == true) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  String html ="<h1>ESP8266 LED Control</h1>";
  html += "<form method='get' action='/'>";
  html += "<input type='submit' name='LED' value='ON'>";
  html += "<input type='submit' name='LED' value='OFF'>";
  html += "</form>";
  html += "</body></html>";
  client.print(html);
  client.println();
  client.println("Connection: close");
  client.println();
}
