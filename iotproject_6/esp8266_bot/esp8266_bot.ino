
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   
#include <Arduino_JSON.h>

const char* ssid = "vakili_4456";
const char* password = "mmzhm_4456";

#define BOTtoken "5817754110:AAGLR1iHNcpKQLbyDNv7U6rK4iUkbX5yMrU"  

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
const int ledPin = D4;
signed long duration_on = 0; // to store the duration of the LED
unsigned long duration_off = 0;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) 
{
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) 
  {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/turn on LED (Time) and turn off LED (Time)  \n";
      welcome += "/state to request current GPIO state \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text.startsWith("turn on LED")) {
      while(1)
      {
      String s1,s2;
      s1=text.substring(0,text.indexOf("and"));
      s2=text.substring(text.indexOf("and")+4);
      String duration_str_on = s1.substring(13); // get the duration string
      String duration_str_off = s2.substring(13); // get the duration string
            duration_on = duration_str_on.toInt();  // convert the duration string to integer
            duration_off = duration_str_off.toInt();convert the duration string to integer
            bot.sendMessage(chat_id, "LED state set to ON For"+ duration_str_on + " seconds and set to OFF for "+duration_str_off + " seconds", "");    
            

      }

      
    }
    
    
    
    if (text == "/state")
     {
      if (digitalRead(ledPin))
        bot.sendMessage(chat_id, "LED is ON", "");
      else
        bot.sendMessage(chat_id, "LED is OFF", "");
      
    }
  }
}

void setup()
 {
    Serial.begin(115200);
    configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
    client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
   {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
}

void loop()
{
   
   
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) 
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
    digitalWrite(ledPin,LOW);
            delay(duration_on);
            digitalWrite(ledPin,HIGH);
            delay(duration_off);
  
}