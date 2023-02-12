#include <ESP8266WiFi.h>
const char* ssid = "xx";
const char* password = "993623042";

WiFiServer server(80);

int ledPin = D4; //pin to connect the LED

unsigned long onDuration = 0;
unsigned long offDuration = 0;
unsigned long previousMillis = 0;
int ledstatus = 1;
bool flag= false;
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {

  WiFiClient client = server.available();
  
    if(flag==false){
    previousMillis = millis();
    flag = true;
    }
    unsigned long currentMillis = millis();
    if (ledstatus==1 && currentMillis - previousMillis >= onDuration && onDuration != 0) {
        digitalWrite(ledPin, HIGH);
        previousMillis = currentMillis;
        ledstatus=0;
    }
    if (ledstatus==0 && currentMillis - previousMillis >= offDuration && offDuration != 0) {
        digitalWrite(ledPin, LOW);
        previousMillis = currentMillis;
        ledstatus=1;
    }
  if (client) {

    {
    Serial.println("new client");
    String request = client.readStringUntil('\r');
    client.flush();
    Serial.println(request);
    if (request.indexOf("/?On=") != -1) {
        int startIndex = (request.indexOf("/?On=") + 5);
        int endIndex = request.indexOf("&", startIndex);
        String onString = request.substring(startIndex, endIndex);
        onDuration = onString.toInt();
    }

    if (request.indexOf("&off=") != -1) {
        int startIndex = request.indexOf("&off=") + 5;
        String offString = "";
        for(int i=startIndex; request[i]!=' '; i++)
        {
          offString+=request[i];
        }
        offDuration = offString.toInt();
    }
    String LEDstatus;
    if (ledstatus==1) {
        LEDstatus = "on";
    } else {
        LEDstatus = "off";
    }
  String html="<html><body>";
  html+="<form action='' method='get' class='form-example'>";
  html+="<label for='ON'>Time(ms) on: </label>";
  html+="<input type='text' name='On' id='On' required><br><br>";
  html+="<label for='OFF'>Time(ms) off: </label>";
  html+="<input type='text' name='off' id='off' required><br><br>";
  html+="<input type='submit' value='Send'>";
  html+="</form></html>";
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.print(html);
    client.println("Connection: close");
    client.println("");
    client.println("");
  }
  }
}