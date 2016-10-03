import socket
import matplotlib.pyplot as plot
import time
import matplotlib.animation as ani


## Socket configuration
HOST = '10.5.3.118'
PORT = 8888

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print ('Socket created')

s.connect((HOST,PORT))


## Controller configuration
kp = 0.16046;
ki = 8.625;
kd = 0;
desired_speed = 110;
error = 0;
cumulative_error = 0;


## Main loop
data = range(1,10)
while(1):

	pulseRPM = float(s.recv(1024))
	print("Recived speed: ", pulseRPM)

	previous_error = error;
	error = desired_speed - pulseRPM;
	diference = error - previous_error;
	cumulative_error += error;

	PID_speed = kp*error + ki*cumulative_error + kd*diference;

	PWM_speed = 0.028*PID_speed*PID_speed - 5.5*PID_speed + 330;


	print("New PWM: ", PWM_speed)
	s.send(PWM_speed)

	data.pop(0)
	data.append(pulseRPM)
	

