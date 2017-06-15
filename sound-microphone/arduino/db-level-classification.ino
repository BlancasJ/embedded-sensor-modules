const double dBAnalogQuiet = 10; // envelope - calibrated value from analog input (48 dB equivalent)
const double dBAnalogModerate = 12;
const double dBAnalogLoud = 17;
int value;
float decibelsValueQuiet;
float decibelsValueModerate;
float decibelsValueLoud;
float valueDb;

void setup() 
{
  Serial.begin(115200);
}


void loop()
{
  value = analogRead(0);
  if(value<13)
  {
    decibelsValueQuiet = 49.5 + calculateDecibels(value, 'q');
    valueDb = decibelsValueQuiet;
  }
  else if ((value > 13) && ( value < 23) )
  {
    decibelsValueModerate = 65.0 + calculateDecibels(value, 'm');
    valueDb = decibelsValueModerate;
  }
  else if(value > 22)
  {
    decibelsValueLoud = 70 + calculateDecibels(value, 'l');
    valueDb = decibelsValueLoud;
  }
  Serial.println(valueDb);
  delay(1000);
}

//20 LOG(X / .775 + 20 LOG (X)

float calculateDecibels(int x, char c)
{
  float decibelsCalculated;
  
    if (c == 'q')
      decibelsCalculated = 20 * log10(x/dBAnalogQuiet);
    if (c == 'm')
      decibelsCalculated = 20 * log10(x/dBAnalogModerate);
    if (c == 'l')
      decibelsCalculated = 20 * log10(x/dBAnalogLoud);  
  
  return (decibelsCalculated);
}
