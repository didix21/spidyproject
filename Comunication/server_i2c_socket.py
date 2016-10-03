import time
import numpy
import socket
import smbus

 
def writeNumber(value):
	bus.write_byte(address, value)
	# bus.write_byte_data(address, 0, value)
	return -1
 
def readNumber():
	number = bus.read_byte(address)
	# number = bus.read_byte_data(address, 1)
	return number

## Socket configuration
HOST = '10.5.3.118'
PORT = 8888

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

s.bind((HOST, PORT))
print 'Socket bind succesful'

s.listen(10) #number of tolerable unaccepted connections

c, addr = s.accept()
print 'Connected with ' + addr[0] + ':' + str(addr[1])


## I2C configuration
# for RPI version 1, use "bus = smbus.SMBus(0)"
bus = smbus.SMBus(1)
address = 0x04

state = 0
## Main loop
while(1):
	writeNumber(100)
	distance_U = float(readNumber())/58 # Read the ultrasound distance

	writeNumber(101)
	accel_X = readNumber()
	accel_X = (readNumber() << 8) | accel_X
	writeNumber(102)
	accel_Y = readNumber()
	accel_Y = (readNumber() << 8) | accel_Y
	writeNumber(103)
	accel_Z = readNumber()
	accel_Z = (readNumber() << 8) | accel_Z
	
	try:	
		if state==0:	
			state = int(s.recv(1024))	#same code as i2c
		if state>=1 && state<=12:
			writeNumber(state)
			pwm_value = int(s.recv(1024))
			writeNumber(pwm_value)
			state = 0;
		if state==100:
			c.send(str(distance_U))
		if state==101:
			c.send(str(accel_X))
		if state==102:
			c.send(str(accel_Y))
		if state==103:
			c.send(str(accel_Z))

	except:
		s.listen(10)
		c, addr = s.accept()

c.close()
s.close()

GPIO.cleanup()
