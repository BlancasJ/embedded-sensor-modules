#include <TH02_dev.h>
float temperature = 0;
float humidity = 0;

void setup() {
  Serial.begin(9600);
  TH02.begin(); 
  delay(100);

}

void loop() {
  temperature = TH02.ReadTemperature();
  humidity = TH02.ReadHumidity();
  delay(100);
  Serial.print(temperature);
  Serial.println(" ºC");
  Serial.print(humidity);
  Serial.println(" %");
  delay(100);
}
