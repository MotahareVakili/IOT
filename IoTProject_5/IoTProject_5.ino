#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
const char* ssid = "xx";
const char* password = "993623042";
int duration_on = 0;
int duration_off = 0;
String serverName = "https://odd-puce-bullfrog-kilt.cyclic.app";
WiFiClient client;
const int ledPin = D4;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

}
void loop() {

  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    String serverPath = serverName ;
    
    http.begin(client,serverPath.c_str());
    // Send HTTP GET request
    int httpResponseCode = http.GET();
    
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String text = http.getString();
      Serial.println(text);
      
      String duration_str_on=text.substring(text.indexOf("ON=")+3,text.indexOf("&"));
      String duration_str_off=text.substring(text.indexOf("OFF=")+4,text.indexOf("&"));
      duration_on = duration_str_on.toInt();  // convert the duration string to integer
      duration_off = duration_str_off.toInt();
      
      digitalWrite(ledPin,LOW);
      delay(duration_on);
      digitalWrite(ledPin,HIGH);
      delay(duration_off);
        
          
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }else {
    Serial.println("WiFi Disconnected");
  }
}