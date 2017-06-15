int value,cont=0;
float valuedb=0,value2;
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
    valuedb = value*(3300/1023);
    value2=valuedb/10;
    result += value2;
    cont++;
    delay(0.1);
  }
  result = result/10000;
  Serial.println(result);
  cont = 0;
}
