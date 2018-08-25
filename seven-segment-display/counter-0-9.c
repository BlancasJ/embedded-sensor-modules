#INCLUDE <18F4550.h>
#USE DELAY(CLOCK=8000000)
#FUSES NOWDT,NOMCLR,INTRC_IO

char display[]=(0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67);
int cont=0;

void main()
{

   while (TRUE)
   {
      if (cont==10)
      {
         cont = 0;
      }
      while (CONT<10)
      {
         output_b(display[cont]);
         cont++;
         delay_ms(1000);
      }
   }
}
