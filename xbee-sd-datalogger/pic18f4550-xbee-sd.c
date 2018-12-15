// Read and write files to and from SD card using PIC18F4550 microcontroller
/*
PINOUT CONNECTION
-SDCS C6
-MOSI C7
-SCK  B1
-MISO B0
*/

#define MMCSD_SPI_HW                
#define MMCSD_PIN_SELECT  PIN_C6

#include <18F4550.h>
#device PASS_STRINGS = IN_RAM
#FUSES PLL1, CPUDIV1, NOMCLR, NOWDT, INTRC
#use delay(clock = 8MHz)
#use rs232(baud=9600, xmit=PIN_C0, rcv=PIN_C1,bits=8,parity=N, stream=DATO) 
#include <string.h>
#use fast_io(D)
// Include MMC/SD card driver source file
#include <mmcsd_m.c>

// Include FAT library source file
#include <fat_m.c>

char frase[]="PIC18F4550 DATALOGGER";
char txt[40];
//char txt1[40];
//char prueba[]="Hola";
char rxString[10];
int8 i;
FILE myfile;

void EscrituraSD()
{

  if(i != 0)
  {
  }
  else 
  {
    // Create a text file 'log.txt'
    if(mk_file("/log.txt") == 0)
    {
    }
    else
    {
    }
    delay_ms(100);
    // Open the last created file 'log.txt' with write permission ('w')
    if(fatopen("/log.txt", "w", &myfile) != 0)
    {
    }
    else 
    {
      delay_ms(100);
      // Write some thing to the text file
      if(i==0)
      {
            sprintf(txt, "\n\r%s", frase);
            fatputs(txt, &myfile);                  
      }
      else
      {
      }
      delay_ms(500);
      // Now close the file
      if(fatclose(&myfile) == 0)
      {
      }
      else
      {
      }
    }

  }

  delay_ms(100);
}

void SoloEscritura(char* string)
{  
    if(fatopen("/log.txt", "a", &myfile) != 0)
    {
    }
    else 
    {
      delay_ms(100);
      // Write some thing to the text file
      if(i==0)
      {
            sprintf(txt, "\n\r%s", string);
            fatputs(txt, &myfile);                  
      }
      else
      {
      }
      delay_ms(500);
      // Now close the file
      if(fatclose(&myfile) == 0)
      {
      }
      else
      {
      }
    }
    delay_ms(100);
}

void read_rs(char* answer_esp, int16 wait_time, int8 lenghtstr)
{
   int8 i=0;
   int16 t1=0,t2=0,t_cont=0;
   
   //Lee la cadena de caracteres hasta que se acabe el tiempo o el número de caracteres de la cadena receptora
   //Para calcular el tiempo de espera se considera:
   //un reloj de 48MHz=> tc=20.8333ns;   4 pulsos de reloj por instrucción => ti=tc * 4 = 83,33ns
   //y que un loop del while utiliza aproximadamente 20 instrucciones de ensamblador => tl = ti * 20 = 1.66 us
   //para llegar a una decima de segundo se requieren: 0.1s/1.66us = 60,000 cuentas.
   while((t_cont < wait_time) && (i<(lenghtstr-1)))
   {
      if (kbhit()) 
      {
         answer_esp[i]= getc(); 
         i++; 
      }
      t1++;
      if(t1>10000)
      {
         t2++; 
         t1=0;
         if(t2>10) 
         {
            t_cont ++; 
            t2=0;
         }
      }
   }
   //Rellena el resto de la cadena con 0s para el fin de línea
   answer_esp[i]=0;
   for (i=i ;i<lenghtstr;i++)
   {
      answer_esp[i]=0;
   }
   if(answer_esp[0]!=0)
   {
      SoloEscritura(answer_esp);
   }
}

void main() 
{

  // Initializing the FAT library as well as the SD card returns 0 if OK
  i = fat_init();
  EscrituraSD();
  while(TRUE)
  {
      read_rs(rxString, 15,10);
  }

}
// End of code
