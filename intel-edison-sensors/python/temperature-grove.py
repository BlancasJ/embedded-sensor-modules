import pyupm_grove   # Get the UPM library

# Create the temperature sensor object
temp = pyupm_grove.GroveTemp(1)

# Use "value" method on it to get the temperature
print "Temperature now is " + str(temp.value())
