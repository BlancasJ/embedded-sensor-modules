import mraa
import time
import math

# More info here -> http://www.seeedstudio.com/wiki/Grove_-_Temperature_Sensor

B=3975
ain = mraa.Aio(1)
a = ain.read()
resistance = (1023-a)*10000.0/a
temp = 1/(math.log(resistance/10000.0)/B+1/298.15)-273.15
print "Temperature now is " + str(temp)
