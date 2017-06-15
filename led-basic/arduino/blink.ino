const int led = 2;
//const int button = 3;
//int val = 0;

void setup() 
{
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  //pinMode(button, INPUT);
}

void loop() 
{
  //val = digitalRead(led);
  //if(val == HIGH)
  //{
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
  //}
}
