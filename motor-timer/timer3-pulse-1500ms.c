/*
This code generates a signal with 1.5 seconds every 500 micro seconds
The main function is making a signal which can shoot a power device (in this case an engine)
*/


#include <18f4550.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8000000)

int cont = 0;
#int_timer3
void motor()             // Here, the signal of 1.5 seconds is generated
{
   cont++;
   if(cont==150)
   {
      output_low(pin_b5);
      delay_us(500);
      output_high(pin_b5);
      cont=0;
   }
   clear_interrupt(int_timer3);
}

void main()             // Here, we set the timer 3
{
   setup_timer_3(T3_INTERNAL|T3_DIV_BY_1);
   set_timer3(45535);  
   enable_interrupts(int_timer3);
   //enable_interrupts(int_rda);
   enable_interrupts(global);
   //clear_interrupt(int_rda);
   clear_interrupt(int_timer3);
   //setup_adc(ADC_CLOCK_INTERNAL);
   //setup_adc_ports(AN0);
   //set_adc_channel(0);
   //lcd_init();
   //output_high(pin_b5);
   while(true)
   {

   }
}
