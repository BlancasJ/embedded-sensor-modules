#include <18F4550.h>
#device adc=10
//#fuses pll1, cpudiv1, nomclr, nowdt, usbdiv, hspll
#fuses HSPLL,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL1,CPUDIV1,VREGEN,NOPBADEN
#use delay(clock=48M)

#include <usb_desc_cdc.h>
#include <usb_cdc.h>
#include <stdlib.h>
#include <stdlibm.h>
#include <stdio.h>
#include <string.h>

#byte ADCON0   =  0x0FC2

unsigned int16 vallm35=0,valdht11=0;
float templm35=0.0,humdht11=0.0;
char data_send[30];

void main(void)
{
   /////Enable Interrupts///////
   enable_interrupts(global);
   enable_interrupts(int_usb);
   /////INICIALIZANDO VARIABLES LOCALES//
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_TO_AN1);
   //usb_cdc_init();
   usb_init_cs();
   //////SECCION DEL PROGRAMA////
   while(true)
   {
      usb_task();
      //
      set_adc_channel(0);
      delay_ms(40);
      read_adc(ADC_START_ONLY);
      while(bit_test(ADCON0,1));
      vallm35 = read_adc(ADC_READ_ONLY);
      templm35 = vallm35*(500.0/1023.0);
      //
      set_adc_channel(1);
      delay_ms(40);
      read_adc(ADC_START_ONLY);
      while(bit_test(ADCON0,1));
      valdht11 = read_adc(ADC_READ_ONLY);
      humdht11 = valdht11*(5.0/1023.0);
      //
      sprintf(data_send,"%2.2f,%2.2f",templm35,humdht11);
      printf(usb_cdc_putc,"%s\r\n",data_send);
      delay_ms(1000);
   }
}
