#include <18f4550.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8M)

int8 state_one[] = {0x00,0x21,0x33,0x3f,0x00,0x0c,0x1e,0x3f};
int8 state_two[] = {0x00,0x01,0x05,0x15,0x00,0x20,0x28,0x2a,0x02,0x3f};
int8 state_three[] = {0x00,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x1f,0x0f,0x07,0x03,0x01,0x00};
int cont=0;
int8 size;

void sequence(int8 *states, int8 size);

#int_ext
void led_seq(void)
{
  cont++;
}

void main()
{
   ext_int_edge(0,L_TO_H);
   enable_interrupts(int_ext);
   enable_interrupts(GLOBAL);
   output_a(0x00);
   while(true)
   {
      switch(cont)
        {
         case 1: size = sizeof(state_one); sequence(state_one,size);
            break;
         case 2: size = sizeof(state_two); sequence(state_two,size);
            break;
         case 3: size = sizeof(state_three); sequence(state_three,size); cont=0;
         default: output_a(0x00);
        }
   }

}

void sequence(int8 *states, int8 size)
{
   for(int i=0;i<size;i++)
   {
      output_a(states[i]);
      delay_ms(500);
   }
}


