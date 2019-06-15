#include<18f4550.h>
#device adc=10
#fuses pll1,nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8M)
#use rs232(uart1, baud=9600)

//defines
#define led_red  pin_a3

//Variables
int8 cont=0;
//int8 *messagepc[];
int16 lm35v=0;

//Functions
void send_data(int16 adc_value);
void receive_data(int8 *message, int16 wait_time, int8 lenghtstr);

#int_timer3
void readTemp()
{
   cont++;
   if(cont==40)
   {
      lm35v = read_adc();
      send_data(lm35v);
      /*receive_data(messagepc,3,5);
      if(messagepc[0] == 0x5f)
      {
         output_high(led_red);
      }
      else if(messagepc[0] == 0x6e)
      {
         output_low(led_red);
      }*/
      cont=0;
   }
   clear_interrupt(int_timer3);
   set_timer3(15535);
}

void main()
{
   setup_timer_3(T3_INTERNAL|T3_DIV_BY_1);
   set_timer3(15535);
   enable_interrupts(GLOBAL);
   enable_interrupts(int_timer3);
   clear_interrupt(int_timer3);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_TO_AN1);
   set_adc_channel(1); 
   output_low(led_red);
   while(true)
   {
      
   }
}

void send_data(int16 adc_value)
{
   int8 adc_msb=0,adc_lsb=0,cs=0;
   //Cabecera
   putc(0x38); //56
   //Start Byte
   putc(0x3c); //60
   //Value for ADC
   adc_msb = make8(adc_value,1);
   adc_lsb = make8(adc_value,0);
   putc(adc_msb);
   putc(adc_lsb);
   //Separator
   putc(0x42); //66
   //CheckSum
   cs = 0x38 + 0x3c + adc_msb + adc_lsb + 0x42;
   putc(cs);
   
}

void receive_data(int8 *message, int16 wait_time, int8 lenghtstr)
{
   int8 i=0;
   int16 t1=0,t_cont=0;
   //Lee la cadena de caracteres hasta que se acabe el tiempo o el número de caracteres de la cadena receptora
   //Para calcular el tiempo de espera se considera:
   //un reloj de 8MHz=> tc=125ns;   4 pulsos de reloj por instrucción => ti=tc * 4 = 500ns
   //y que un loop del while utiliza aproximadamente 20 instrucciones de ensamblador => tl = ti * 20 = 10 us
   //para llegar a una decima de segundo se requieren: 0.1s/10us = 10,000 cuentas.
   while((t_cont < wait_time) && (i<lenghtstr))
   {
      if (kbhit()) 
      {
         message[i]= getc(); 
         i++; 
      }
      t1++;
      IF (t1>10000)
      {
         t1=0;
         t_cont++;
      }
   }
   //Rellena el resto de la cadena con 0s para el fin de línea;
   for (int j=i ;j<lenghtstr;j++)
   {
      message[j]=0;
   }
}
