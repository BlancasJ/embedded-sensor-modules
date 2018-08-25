import time
import mraa
import pyupm_guvas12d as upmUV #Lib for UV Sensor
import pyupm_i2clcd as lcd

StatusLed = mraa.Gpio(13) #Statys Led Variables
UV = upmUV.GUVAS12D(1)

#Operating voltage for UV sensor
GUVAS12D_AREF = 5.0
SAMPLES_PER_QUERY = 1024

#Set to OUTPUT
StatusLed.dir(mraa.DIR_OUT)

# Initialize Jhd1313m1 at 0x3E (LCD_ADDRESS) and 0x62 (RGB_ADDRESS)
myLcd = lcd.Jhd1313m1(0, 0x3E, 0x62)

myLcd.setCursor(0,0)
# RGB Blue
myLcd.setColor(0, 0, 255)

while True:
        s = UV.value(GUVAS12D_AREF, SAMPLES_PER_QUERY)  # Read of UV
        s = s / 200
        print s
        if s<=2:
            StatusLed.write(0) #Turn on RedLed if UV its not OK
            myLcd.write(("%f BAJO")%s)
            myLcd.setCursor (1,0)
            myLcd.write("FPS 15")
        elif 2 < s <= 5:
            StatusLed.write(0)  # Turn on RedLed if UV its not OK
            myLcd.write(("%f MODERADO")%s)
            myLcd.setCursor(1,0)
            myLcd.write("FPS 30")
        elif 5 < s <= 7:
            StatusLed.write(1)
            myLcd.write(("%f ALTO")&s)
            myLcd.setCursor(1,0)
            myLcd.write("FPS 50")
        elif 7 < s <= 10:
            StatusLed.write(1)
            myLcd.write(("%f MUY ALTO")%s)
            myLcd.setCursor(1,0)
            myLcd.write("FPS 50")
        elif s > 10:
            StatusLed.write(1)
            myLcd.write(("%f EXTREMO")%s)
            myLcd.setCursor(1,0)
            myLcd.write("FPS 60")
        time.sleep(5)
        myLcd.clear()


