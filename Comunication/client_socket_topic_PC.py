#! /usr/bin/env python

import socket
import matplotlib.pyplot as plot
import time
import matplotlib.animation as ani

import rospy


pwm_values = [0,0,0,0,0,0,0,0,0,0,0,0]
distance_U = 0
accel_X = 0
accel_Y = 0
accel_Z = 0
gyro_X = 0
gyro_Y = 0
gyro_Z = 0

"""
ArduinoController runs the services related with the arduino:
	/arduino/ultrasound
	/arduino/accel
	/arduino/pwm
"""
def pwm_service_cb(req):
	#callback of pwm_service

#!/usr/bin/python

def main():
	rospy.loginfo("Initializing client_socket_topic")
	## Socket configuration
	HOST = '10.5.3.118'
	PORT = 8888

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	rospy.loginfo('Socket created')

	s.connect((HOST,PORT))


	PWMservice = rospy.Service('/pwm_service', PWMService, pwm_service_cb)
	#self.usersaid_pub = rospy.Publisher('/asr_event', ASREvent)

	## Main loop
	while(1):	

		s.send(100)
		distance_U = int(s.recv(1024))

		s.send(101)
		accel_X = int(s.recv(1024))
		s.send(102)
		accel_Y = int(s.recv(1024))
		s.send(103)
		accel_Z = int(s.recv(1024))

		s.send(104)
		gyro_X = int(s.recv(1024))
		s.send(105)
		gyro_Y = int(s.recv(1024))
		s.send(106)
		gyro_Z = int(s.recv(1024))

		for i in range(1,13):
			s.send(i)
			s.send(pwm_values[i])




if __name__ == '__main__':
	rospy.init_node('client_socket_topic')
	rospy.loginfo("Initializing client_socket_topic")
	main()


