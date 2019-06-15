#include <18f4550.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8M)

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>

int contin=0,contotal=0;

#int_ext
void person_in()
{
   contin++;
   contotal++;
   clear_interrupt(int_ext);
   clear_interrupt(int_ext1);
}
#int_ext1
void person_out()
{
   contin--;
   clear_interrupt(int_ext);
   clear_interrupt(int_ext1);
}

void main()
{
   enable_interrupts(GLOBAL);
   enable_interrupts(int_ext);
   enable_interrupts(int_ext1);
   ext_int_edge(0,H_TO_L);
   ext_int_edge(1,H_TO_L);
   lcd_init();
   while(true)
   {
      lcd_gotoxy(1,1);
      printf(lcd_putc,"\fTotal People: %i",contotal);
      lcd_gotoxy(0,0);
      printf(lcd_putc,"Current People: %i",contin);
   }
}
