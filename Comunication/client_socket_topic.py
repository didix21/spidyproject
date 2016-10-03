#! /usr/bin/env python

import socket
import matplotlib.pyplot as plot
import time
import matplotlib.animation as ani

import rospy

#TODO port this code to C++ to ease compatibility with the rest of the team

class ArduinoController:
	"""
	ArduinoController runs the services related with the arduino:
		/arduino/ultrasound
		/arduino/accel
		/arduino/pwm
	"""
	def __init__(self):
		rospy.loginfo("Initializing client_socket_topic")
		## Socket configuration
		HOST = '10.5.3.118'
		PORT = 8888

		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		rospy.loginfo('Socket created')

		self.s.connect((HOST,PORT))


		## Controller configuration
		self.pwm_values = [0,0,0,0,0,0,0,0,0,0,0,0]

	
	def execute(self,goal):
		## Main loop
		while(1):	
	
			self.s.send(100)
			self.distance_U = int(s.recv(1024))

			self.s.send(101)
			self.accel_X = int(s.recv(1024))
			self.s.send(102)
			self.accel_Y = int(s.recv(1024))
			self.s.send(103)
			self.accel_Z = int(s.recv(1024))

			for i in range(1,13):
				self.s.send(i)
				self.s.send(pwm_values[i])



if __name__ == '__main__':
	rospy.init_node('client_socket_topic')
	rospy.loginfo("Initializing client_socket_topic")
	server


