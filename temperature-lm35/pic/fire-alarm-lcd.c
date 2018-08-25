#include <18f4550.h>
#device adc=10
#fuses nomclr,nowdt,intrc_io
#use delay(clock=8000000)
//#use rs232(uart1, baud=9600)

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>
float temp;
int lm35v=0,cont=0;
#int_timer3
void temperature()
{
   cont++;
   if(cont==100)
   {
      lm35v = read_adc();
      temp = lm35v*0.48;
      printf(lcd_putc,"\f");
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Temp = %f",temp);
      if(temp>40)
      {
         lcd_gotoxy(1,1);
         printf(lcd_putc,"\fFIRE!!!");
      }
      else
      {
         lcd_gotoxy(0,0);
         printf(lcd_putc,"Fine");
      }
   }
   enable_interrupts(int_timer3);
   clear_interrupt(int_timer3);
}

void main()
{
   lcd_init();
   setup_timer_3(T3_INTERNAL|T3_DIV_BY_1);
   set_timer3(45535);
   enable_interrupts(GLOBAL);
   enable_interrupts(int_timer3);
   clear_interrupt(int_timer3);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   set_adc_channel(0);
   
   while(true)
   {
      lcd_gotoxy(0,0);
      printf(lcd_putc,"HI");
      delay_ms(1000);
   }
}
