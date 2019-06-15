#include <18f4550.h>
#fuses pll1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8M)

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>

int counter = 0;

#int_ext
void count(void)
{
   while(counter<9)
   {
      counter++;
      printf(lcd_putc,"\fCounter: %i",counter);
      delay_ms(1000);
   }
   counter = 0;
   printf(lcd_putc,"\fCounter: %i",counter);
}

void main()
{
   ext_int_edge(0,L_TO_H);
   enable_interrupts(int_ext);
   enable_interrupts(GLOBAL);
   lcd_init();
   printf(lcd_putc,"\fCounterr: 0-9");
   while(true)
   {
      
   }

}

