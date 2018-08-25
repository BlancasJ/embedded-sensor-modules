#include <18f4550.h>
//#device adc=10
#include <string.h>
#include <stdlib.h>
#include <math.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1,xt
#use delay(clock=8000000)
//#use rs232(uart1, baud=9600)

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
//#define use_portb_kbd TRUE
#include <lcd.c>
#include <kbd2.c>

/*char tecla_time(void) {
   char c='\0';
   unsigned int16 timeout;
   timeout=0;
   c=kbd_getc(); //Captura valor del teclado
   while(c=='\0' && (++timeout< (200*100)))
   {
      delay_us(10);
      c=kbd_getc(); //Captura valor del teclado
   }
   return(c);
}
*/

void main()
{
   //setup_timer_3(T3_INTERNAL|T3_DIV_BY_1);
   //set_timer3(45535);
   //enable_interrupts(int_timer3);
   //enable_interrupts(int_rda);
   //enable_interrupts(global);
   //clear_interrupt(int_rda);
   //clear_interrupt(int_timer3);
   //setup_adc(ADC_CLOCK_INTERNAL);
   //setup_adc_ports(AN0);
   //set_adc_channel(0);
   char k;
   port_b_pullups(true);
   lcd_init();
   kbd_init();
   while(true)
   {
      printf(lcd_putc,"\f");
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Write a number");
      k=kbd_getc();
      if(k!=0)
      {
         lcd_gotoxy(0,0);
         printf(lcd_putc,"%c",k);
      }
      delay_ms(1000);
   }
}
