#include <ESP8266WiFi.h>
#include "WifiLocation.h"

#define GOOGLE_KEY "YOUR_GOOGLE_API_KEY"
#define SSID "NETWORK_NAME"
#define PASSWD ""

WifiLocation location(GOOGLE_KEY);

void setup() {
  Serial.begin(115200);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(SSID);
    // Connect to WPA/WPA2 network:
    WiFi.begin(SSID, PASSWD);
    // wait 5 seconds for connection:
    delay(5000);
    Serial.print("Status = ");
    Serial.println(WiFi.status());
  }
  location_t loc = location.getGeoFromWiFi();

  Serial.println("Location request data");
  Serial.println(location.getSurroundingWiFiJson());
  Serial.println("Latitude: " + String(loc.lat, 7));
  Serial.println("Longitude: " + String(loc.lon, 7));
  Serial.println("Accuracy: " + String(loc.accuracy));
  
}

void loop() {

}
