#include <18f4550.h>
#device ADC=10
#fuses nomclr,nowdt,intrc_io
#use delay(clock=8000000)
#define LCD_ENABLE_PIN PIN_B0
#define LCD_RS_PIN PIN_B1
#define LCD_RW_PIN PIN_B2
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7 
#include <lcd.c>
#include <math.h>

float analogValue;
float resistanceLDR;
float lux;
float Vout;
float analogLM35;
float temp;

void main()
{
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   set_adc_channel(0);
   lcd_init();
   //configurar timers
   while (TRUE)
   {
      analogValue = read_adc(0);
      analogLM35 = read_adc(1);
      
      Vout = (analogValue * 0.0048828125);
      resistanceLDR = (5 - Vout)/Vout;
      lux = 10000 / (pow (resistanceLDR*10,(4/3)));
      lcd_gotoxy(1,1);
      if (lux < 300)
      {
         output_high(PIN_C1);
      }
      else
      {
         output_low(PIN_C1);
      }
      printf(lcd_putc, "LUX = %f",lux);
      //delay_ms(3000); cambiar usando timer
      lcd_putc('\f');
    }
 }

