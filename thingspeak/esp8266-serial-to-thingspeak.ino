#include <ESP8266WiFi.h>

// Wi-Fi Settings
const char* ssid = "NETWORK_NAME"; // your wireless network name (SSID)
const char* password = "PASSWORD"; // your Wi-Fi network password
//const char* ssid = "itmerida"; // your wireless network name (SSID)
//const char* password = ""; // your Wi-Fi network password

WiFiClient client;

// ThingSpeak Settings
const int channelID = YOUR_CHANNEL_ID;
String writeAPIKey = "YOUR_THINGSPEAK_API_KEY";
const char* server = "api.thingspeak.com";
//const int postingInterval = 15 * 1000; // post data every 20 seconds

int Cans_counter;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("estoy aqui");

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.println("estoy en while wifistatus");
    Serial.println("*");
  }
}

void loop() {
  if(Serial.available())
  {
    if (client.connect(server, 80)) 
    {
          Cans_counter = Serial.read();
          
          String body = "field1=" + String(Cans_counter);
          
      
          client.println("POST /update HTTP/1.1");
          client.println("Host: api.thingspeak.com");
          client.println("User-Agent: ESP8266 (nothans)/1.0");
          client.println("Connection: close");
          client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey);
          client.println("Content-Type: application/x-www-form-urlencoded");
          client.println("Content-Length: " + String(body.length()));
          client.println("");
          client.print(body);
    }
  }


}
