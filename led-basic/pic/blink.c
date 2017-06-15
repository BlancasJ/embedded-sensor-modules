#include <18f4550.h>
#device adc=10
#fuses nomclr,nowdt,intrc_io
#use delay(clock=8000000)
//#use rs232(uart1, baud=9600)

void main()
{
   while(1)
   {
      output_toggle(pin_a1);
      delay_ms(1000);
   }
}
