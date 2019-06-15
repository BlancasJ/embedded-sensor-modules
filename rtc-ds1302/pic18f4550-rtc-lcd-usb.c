#include <18F4550.h>
#device ADC=10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48000000)  //#use delay(clock=20000000)
#include <usb/usb_bootloader.h> //Comenta esta línea si no usas Bootloader
#include <JACSS_CDC.c>  //Libreria que genera el puerto COM virtual para comunicacion.
#include <DS1302RTC.c>

#define LCD_RS_PIN PIN_D0
#define LCD_RW_PIN PIN_D1
#define LCD_ENABLE_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>

int8 days=16;
int8 months=6;
int8 years=19;
int8 dows=07;
int8 hours=01;
int8 minutes=36;

int8 day1=0;
int8 month1=0;
int8 year1=0;
int8 dow1=0;
int8 hour1=0;
int8 minute1=0;
int8 second1=0;

char diatxt[3];
char mestxt[3];
char anotxt[3];
char horatxt[3];
char minutotxt[3];
char segundotxt[3];


void main()
{
   lcd_init();
   rtc_init();
   delay_ms(100);
   //rtc_set_datetime(days,months,years,dows,hours,minutes);
   delay_ms(100);
   while(true)
   {
      rtc_get_time(hour1, minute1, second1);
      rtc_get_date(day1, month1, year1, dow1);
      //Sprintf for adding zeros
      sprintf(diatxt, "%02d", day1);   
      sprintf(mestxt, "%02d", month1);
      sprintf(anotxt, "%02d", year1);
      sprintf(horatxt, "%02d", hour1);
      sprintf(minutotxt, "%02d", minute1);
      sprintf(segundotxt, "%02d", second1);
      
      lcd_putc("\f");
      lcd_gotoxy(0,1);
      printf(lcd_putc,"Time: %s:%s:%s",horatxt,minutotxt,segundotxt);
      lcd_gotoxy(0,0);
      printf(lcd_putc,"Date: %s/%s/%s", diatxt, mestxt, anotxt);
      delay_ms(1000);
   }
}
