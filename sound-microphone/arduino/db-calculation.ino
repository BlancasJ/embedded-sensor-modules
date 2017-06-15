int value,cont=0;
float valuedb=0;
float result=0;

void setup() 
{
  Serial.begin(115200);
}


void loop()
{
  value = analogRead(0);
  while(cont<10000)
  {
    valuedb = (20 * log10((value*value)/0.775))-30;
    result += valuedb;
    cont++;
    delay(0.1);
  }
  result = result/10000;
  Serial.println(result);
  cont = 0;
  //delay(1000);
}
