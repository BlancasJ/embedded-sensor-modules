#include <18f4550.h>
#fuses PLL1, nomclr,nowdt,intrc,cpudiv1
#use delay(clock=8M)
#use fast_io(A)
#define DHT11_PIN PIN_A4   // Connection pin between DHT11 and mcu

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <lcd.c>
 
char message1[] = "Temp = 00.0 C  ";
char message2[] = "RH   = 00.0 %  ";
short Time_out;
unsigned int8 T_byte1, T_byte2, RH_byte1, RH_byte2, CheckSum;

void start_signal(){
  output_drive(DHT11_PIN);                            // Configure connection pin as output
  output_low(DHT11_PIN);                              // Connection pin output low
  delay_ms(25);
  output_high(DHT11_PIN);                             // Connection pin output high
  delay_us(30);
  output_float(DHT11_PIN);                            // Configure connection pin as input
}
short check_response(){
  delay_us(40);
  if(!input(DHT11_PIN)){                              // Read and test if connection pin is low
    delay_us(80);
    if(input(DHT11_PIN)){                             // Read and test if connection pin is high
      delay_us(50);
      return 1;
    }
  }
}
unsigned int8 Read_Data(){
  unsigned int8 i, k, _data = 0;                      // k is used to count 1 bit reading duration
  if(Time_out)
    break;
  for(i = 0; i < 8; i++){
    k = 0;
    while(!input(DHT11_PIN)){                         // Wait until DHT11 pin get raised
      k++;
      if(k > 100){
        Time_out = 1;
        break;
      }
      delay_us(1);
    }
    delay_us(30);
    if(!input(DHT11_PIN))
      bit_clear(_data, (7 - i));                      // Clear bit (7 - i)
    else{
      bit_set(_data, (7 - i));                        // Set bit (7 - i)
      while(input(DHT11_PIN)){                        // Wait until DHT11 pin goes low
        k++;
        if(k > 100){
        Time_out = 1;
        break;
      }
      delay_us(1);}
    }
  }
  return _data;
}

void main() {
  lcd_init();                                   // Initialize LCD module
  printf(lcd_putc,"\f");                                 // LCD Clear
  delay_ms(1000);
  while(true){
    Time_out = 0;
    Start_signal();
    if(check_response())                              // If there is a response from sensor
    {                             
      RH_byte1 = Read_Data();                         // read RH byte1
      RH_byte2 = Read_Data();                         // read RH byte2
      T_byte1 = Read_Data();                          // read T byte1
      T_byte2 = Read_Data();                          // read T byte2
      Checksum = Read_Data();                         // read checksum
      if(Time_out)
      {                                   // If reading takes long time
        lcd_gotoxy(1, 1);                               // Go to column 5 row 1
        printf(lcd_putc,"\fTime out!");
      }
      else
      {
       if(CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF)){
         message1[7]  = T_Byte1/10  + 48;
         message1[8]  = T_Byte1%10  + 48;
         message1[10] = T_Byte2/10  + 48;
         message2[7]  = RH_Byte1/10 + 48;
         message2[8]  = RH_Byte1%10 + 48;
         message2[10] = RH_Byte2/10 + 48;
         message1[11] = 223;                          // Degree symbol
         lcd_gotoxy(1, 1);                              // Go to column 1 row 1
         printf(lcd_putc,"\f%s", message1);                   // Display message1
         lcd_gotoxy(0, 0);                              // Go to column 1 row 2
         printf(lcd_putc,"\f%s", message2);                   // Display message2
       }
       else
       {
         lcd_gotoxy(1, 1);                              // Go to column 1 row 1
         printf(lcd_putc,"\fChecksum Error!");
       }
      }
    }
    else 
    {
      lcd_gotoxy(1, 1);                                 // Go to column 3 row 1
      printf(lcd_putc,"\fNo response");
      lcd_gotoxy(0, 0);                                 // Go to column 1 row 2
      printf(lcd_putc,"from the sensor");
    }
  delay_ms(1000);
  }
}

