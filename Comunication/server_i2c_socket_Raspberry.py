
#!/usr/bin/python

import time
import numpy
import socket
import smbus

def read_word(address, register):
	high = bus.read_byte_data(address, register)
	low = bus.read_byte_data(address, register+1)
	val = (high << 8) + low

	if (val >= 0x8000):
		return -((65535 - val) + 1)
	else:
		return val


def init_accelerometer():
	bus.write_byte_data(address, 0x6B, 0) #wake up sensor - power management


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
arduino_address = 0x04
accel_address = 0x68

init_accelerometer()

state = 0
## Main loop
while(1):
	bus.write_byte(arduino_address, 100)	# Request ultrasound distance
	distance_U = float(bus.read_byte(arduino_address))/58 # Read the ultrasound distance

	accel_X = read_word(accel_address, 0x3b)
	accel_Y = read_word(accel_address, 0x3d)
	accel_Z = read_word(accel_address, 0x3f)

	gyro_X = read_word(accel_address, 0x43)
	gyro_Y = read_word(accel_address, 0x45)
	gyro_Z = read_word(accel_address, 0x47)
	
	try:	
		if state==0:	
			state = int(s.recv(1024))	#same protocol as i2c
		if state>=1 and state<=12:
			bus.write_byte(arduino_address, state)
			pwm_value = int(s.recv(1024))
			bus.write_byte(arduino_address, pwm_value)
			state = 0;
		if state==100:
			c.send(str(distance_U))
			state = 0;
		if state==101:
			c.send(str(accel_X))
			state = 0;
		if state==102:
			c.send(str(accel_Y))
			state = 0;
		if state==103:
			c.send(str(accel_Z))
			state = 0;
		if state==104:
			c.send(str(gyro_X))
			state = 0;
		if state==105:
			c.send(str(gyro_Y))
			state = 0;
		if state==106:
			c.send(str(gyro_Z))
			state = 0;

	except:
		s.listen(10)
		c, addr = s.accept()

c.close()
s.close()

GPIO.cleanup()
