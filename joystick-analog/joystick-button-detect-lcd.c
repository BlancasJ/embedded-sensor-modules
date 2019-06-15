#include<18f4550.h>
#device adc=10 //analog digital converter
#fuses nomclr,intrc,pll1,nowdt
#use delay(clock=8M)

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>

int16 potx=0,poty=0;
float val_resx=0.0,val_resy=0.0;

void main()
{
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_to_AN1);
   lcd_init();
   lcd_gotoxy(1,1);
   while(true)
   {
      set_adc_channel(0);
      potx = read_adc();
      delay_us(10);
      set_adc_channel(1);
      poty = read_adc();
      delay_us(10);
      val_resx = (potx*128.0)/1024.0;
      val_resy = (poty*64.0)/1024.0;
      if(val_resx>=10 && val_resx<=54 && val_resy>=15 && val_resy<= 49)
      {
         printf(lcd_putc,"\fBUTTON 1 ON");
      }
      else if(val_resx>=74 && val_resx<=118 && val_resy>=15 && val_resy<= 49)
      {
         printf(lcd_putc,"\fBUTTON 2 ON");
      }
      else
      {
         printf(lcd_putc,"\f");
      }
      delay_ms(100);
   }
}

