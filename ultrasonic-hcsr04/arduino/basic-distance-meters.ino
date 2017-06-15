int pecho = 2;            // define el pin 2 como (pecho) para el Ultrasonido
int ptrig = 3;            // define el pin 3 como (ptrig) para el Ultrasonido
float duracion, distancia;  // para Calcular distacia

void setup()  { 
  Serial.begin(9600);
  pinMode(pecho, INPUT);   // define el pin 2 como entrada (pecho) 
  pinMode(ptrig,OUTPUT);   // define el pin 3 como salida  (ptrig) 
  pinMode(13,OUTPUT);
} 
void loop(){
  
  digitalWrite(ptrig, HIGH);   // genera el pulso de trigger por 10us
  delay(0.01);
  digitalWrite(ptrig, LOW);
     
  duracion = pulseIn(pecho, HIGH);              // Lee el tiempo del Echo
  distancia = (((duracion/2) / 29) /100);            // calcula la distancia en centimetros
  delay(10);
  Serial.println(distancia);
  delay(100);
  
  }
