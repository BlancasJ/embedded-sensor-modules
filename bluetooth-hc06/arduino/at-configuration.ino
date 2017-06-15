const int BT = 12;

char nameBT[10] = "Roboticarm";
char pin[5] = "SAPO";
char revolutions = '4';
char mode = 0;

void setup() {
  pinMode(BT,OUTPUT);
  Serial.begin(38400);

  digitalWrite(BT,HIGH);
  Serial.print("AT\r\n");

  Serial.print("AT+NAME");
  Serial.print(nameBT);
  Serial.print("\r\n");

  Serial.print("AT+PIN");
  Serial.print(pin);
  Serial.print("\r\n");

  Serial.print("AT+BAUD");
  Serial.print(revolutions);
  Serial.print("\r\n");

  Serial.print("AT+MODE");
  Serial.print(mode);
  Serial.print("\r\n");
  
}

void loop() {
}
