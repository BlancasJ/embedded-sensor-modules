/*
Tengo conectado al pin 5 el DHT11
Uso Puerto serial RX0 TX0
*/

//DHT11 CONFIGURACION
#include <DHT.h> 
#define DHTPIN 7          //Pin al cual se conecta el Sensor DHT11
#define DHTTYPE DHT11     //Tipo del Sensor
DHT dht(DHTPIN, DHTTYPE); //Declaracion del objeto DHT

//CONFIGURACION WIFI
#define SSID "NETWORK_NAME"        //Nombre de la Red Wifi a la que nos conectamos
#define PASS "PASSWORD"     //Contraseña de la Red Wifi
#define IP "184.106.153.149" // thingspeak.com 
//Sustituir [WRITE_API_KEY] por la obtenida en thingspeak.com  sin [] 
String GET_TEMP = "GET /update?key=YOUR_THINGSPEAK_API_KEY&field1="; //Campo de temperatura 
String GET_HUM = "GET /update?key=YOUR_THINGSPEAK_API_KEY&field2="; //Campo de humedad
String GET_TEMPLM = "GET /update?key=YOUR_THINGSPEAK_API_KEY&field3=";

void setup()
{
dht.begin();             //Se inicializa sensor DHT
Serial.begin(115200);    //Se inicializa el puerto Serial para comunicarse con el Modulo Wifi ESP8266
delay(5000); //delay para conectar los cables
Serial.println("AT\r");
delay(5000);
if(Serial.find("OK"))
{  //Verificar si Modulo Wifi responde
  connectWiFi();          //Conectarse a la red
}
}

 
void loop()
{ 
//DHT11
float h = dht.readHumidity();       // Lee la humedad 
float t = dht.readTemperature();    //Lee la temperatura 
char bufferTemp[8];                                //Crear buffer temporal para convertir float a string 
String temperatura = dtostrf(t, 4, 1, bufferTemp);  //Convertir de float a String 8 = longitud de String, 3 = numero de decimales. (e.g. 1234.567) 
updateTemp(temperatura);                            //Actualizar temperatura 
delay(20000);                                       //Thingspeak nos pide un MINIMO de 15 segundos entre cada actualizacion  
char bufferHum[8];                                 //Crear buffer temporal para convertir float a string 
String humedad = dtostrf(h, 4, 1, bufferHum);       //Convertir de float a string 8 = longitud de String, 3 = numero de decimales. (e.g. 1234.567) 
updateHumedad(humedad);                             //Actualizar humedad 
delay(20000);                                       //Hacer una medicion cada 60 segundos. (20+40) 
//LM35
float sensor=analogRead(A0);
float voltagemilivolt=(sensor*5000)/1024;
float temperaturalm35=voltagemilivolt/10;
char bufferlm35[8];                                 
String temperaturasensorlm35 = dtostrf(temperaturalm35, 4, 1, bufferlm35);  
updateTemplm35(temperaturasensorlm35);                            
delay(20000);
}


//Temperatura configuracion y envio
 
void updateTemp(String temperatura)
{
String cmd = "AT+CIPSTART=\"TCP\",\"";              //Crear el comando para comenzar una conexion TCP
cmd += IP;                                          //IP del sitio a conectarse (thingspeak.com) 
cmd += "\",80";                                     //Puerto (80) 
Serial.println(cmd);                                //Crear conexion 
delay(2000); 
if(Serial.find("Error"))
{
return;                                           //No se pudo conectar
}
cmd = GET_TEMP;                                     //Crear datos a enviar
cmd += temperatura;                                      //Agregar la temperatura leida
cmd += "\r\n";                                      //Agregar caracteres de newline y Carriage return
Serial.print("AT+CIPSEND=");                        //Indicar cuantos datos se enviaran por TCP
Serial.println(cmd.length());                       //Tamaño de los datos a enviar por TCP
if(Serial.find(">"))
{
Serial.print(cmd);                                //Enviar datos
}
else
{
Serial.println("AT+CIPCLOSE");                    //No se pudo ejecutar, cerrar conexion TCP
}
}


//Humedad configuracion y envio

void updateHumedad(String humedad)
{
String cmd = "AT+CIPSTART=\"TCP\",\""; 
cmd += IP; 
cmd += "\",80";
Serial.println(cmd);
delay(2000);
if(Serial.find("Error"))
{ 
return; 
} 
cmd = GET_HUM; 
cmd +=humedad; 
cmd += "\r\n"; 
Serial.print("AT+CIPSEND="); 
Serial.println(cmd.length()); 
if(Serial.find(">"))
{
Serial.print(cmd);
}
else
{
Serial.println("AT+CIPCLOSE");
}
}


//LM35

void updateTemplm35(String temperaturasensorlm35)
{
String cmd = "AT+CIPSTART=\"TCP\",\"";              //Crear el comando para comenzar una conexion TCP
cmd += IP;                                          //IP del sitio a conectarse (thingspeak.com) 
cmd += "\",80";                                     //Puerto (80) 
Serial.println(cmd);                                //Crear conexion 
delay(2000); 
if(Serial.find("Error"))
{
return;                                           //No se pudo conectar
}
cmd = GET_TEMPLM;                                     //Crear datos a enviar
cmd += temperaturasensorlm35;                                      //Agregar la temperatura leida
cmd += "\r\n";                                      //Agregar caracteres de newline y Carriage return
Serial.print("AT+CIPSEND=");                        //Indicar cuantos datos se enviaran por TCP
Serial.println(cmd.length());                       //Tamaño de los datos a enviar por TCP
if(Serial.find(">"))
{
Serial.print(cmd);                                //Enviar datos
}
else
{
Serial.println("AT+CIPCLOSE");                    //No se pudo ejecutar, cerrar conexion TCP
}
}


//Funcion para crear conexion Wifi. Regresa true si se conecta exitosamente, si no false.
 
boolean connectWiFi()
{
Serial.println("AT+CWMODE=1");
delay(5000);
String cmd="AT+CWJAP=\"";
cmd+=SSID;
cmd+="\",\"";
cmd+=PASS;
cmd+="\"";
Serial.println(cmd);
delay(5000);
if(Serial.find("OK"))
{
return true;
}
else
{
return false;
} 
}
