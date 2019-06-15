/*
Codigo bueno para enviar datos a Thingspeak
*/
#include <18F4550.h>
#device ADC=10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48000000)  //#use delay(clock=20000000)
#include <usb/usb_bootloader.h> //Comenta esta línea si no usas Bootloader
#include <JACSS_CDC.c>  //Libreria que genera el puerto COM virtual para comunicacion.
//#USE RS232(baud=115200,xmit=pin_c6,rcv=pin_c7,bits=8,parity=N)
#use rs232(baud=115200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,ERRORS)

#include <pic_esp8266.h>
#define LCD_RS_PIN PIN_D0
#define LCD_RW_PIN PIN_D1
#define LCD_ENABLE_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>

float valoradc=0.0;
float milivolt=0.0;
float temperatura=0.0;

void ESP8266SetaModoEstacion(void)
{
   puts(modo);
   delay_ms(500);
}

void ESP8266Conectar(void)
{
   puts(conectar);
   delay_ms(5000);
}

void ESP8266MultiplesConexiones(void)
{
   puts(multiple);
   delay_ms(500);
}

void SetupESP8266(void)
{
   ESP8266SetaModoEstacion();
   ESP8266Conectar();
   ESP8266MultiplesConexiones();
}

void ESP8266TCPThingspeak(void)
{
   puts(TCP);
   delay_ms(2000);
}

void ESP8266PreparaEnvio(void)
{
   puts(preparaenvio);
   delay_ms(1000);   
}

void ESP8266EnviarThingspeak(char valor)
{
   char EnvioHTTP[50];

   memset(EnvioHTTP,0,sizeof(EnvioHTTP));
   sprintf(EnvioHTTP,"%s%03d\r\n\0",enviardato1,valor);
   puts(EnvioHTTP);
   delay_ms(2000);
}

void main()
{
   lcd_init();
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   SetupESP8266();
   
   while(true)
   {
   set_adc_channel(0);
   delay_us(10);
   valoradc=read_adc();
   milivolt=(valoradc*5000.0)/1023.0;
   //formula vo=(10mV/C)(T°C)+600
   temperatura=(milivolt-550.0)/10.0;
   lcd_putc("\f");
   lcd_gotoxy(0,1);
   printf(lcd_putc,"Temp; %2.2f", temperatura);
   
   ESP8266TCPThingspeak();
   ESP8266PreparaEnvio();
   ESP8266EnviarThingspeak(temperatura);
   delay_ms(20000);
   }
}
