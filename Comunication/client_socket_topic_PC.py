#! /usr/bin/env python

import socket
import rospy
import actionlib

import action\PWMAction

## Socket address
HOST = '192.168.0.42'
PORT = 8888


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

def pwm_action_cb(goal):
	rospy.loginfo('/arduino/pwm service callback executed')
	PWM_action.set_succeeded()
	#callback of pwm_action

def main():
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	rospy.loginfo('Socket created')

	s.connect((HOST,PORT))
	rospy.loginfo('Socket connected')


	PWM_action = actionlib.SimpleActionServer('/arduino/pwm', PWMAction, pwm_service_cb, False)
	PWM_action.start()
	rospy.loginfo('Action /arduino/pwm launched')

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

		rospy.loginfo('Values sent')




if __name__ == '__main__':
	rospy.init_node('client_socket_topic')
	rospy.loginfo("Initializing client_socket_topic")
	main()


