#include <18f4550.h>
#device adc=10
#include <string.h>
#include <math.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
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

int cont,ldr;
float value,light,resistance;

#int_timer3
void read_light()
{
   cont++;
   if(cont==50)
   {
      ldr = read_adc();
      value = ldr*0.0048828125;
      resistance = (5-value)/value;
      light = 10000 / (pow (resistance*10,(4/3)));
      lcd_putc("\f");
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Light: %f",light);
      cont=0;
   }
   set_timer3(45535);
   clear_interrupt(int_timer3);
}
void main()
{
   setup_timer_3(T3_INTERNAL|T3_DIV_BY_1);
   set_timer3(45535);
   enable_interrupts(int_timer3);
   enable_interrupts(int_rda);
   enable_interrupts(global);
   clear_interrupt(int_rda);
   clear_interrupt(int_timer3);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   set_adc_channel(0);
   lcd_init();
   
   while(true)
   {

   }
}
