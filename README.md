# spidyproject
![version](https://badge.fury.io/gh/didix21%2Fspidyproject.svg)
![travis-build](https://travis-ci.org/didix21/spidyproject.svg?branch=master)
[![HitCount](http://hits.dwyl.io/didix21/spidyproject.svg)](http://hits.dwyl.io/didix21/spidyproject)
## About it
This repository contains all the necessary firmware to be implimented in Arduino's Spidy. Spidy is a six leg robot which is controlled with an Arduino and the spidyfirmware.  
Based on the robot: [Funny six feet + Myo](http://www.thingiverse.com/thing:1201161/#files)

# Characteristics
Description about the hardware and firmware used in spidy.
## Hardware
 * Plastic chasis.
 * Arduino.
 * 16 channels pwm controller.
 * 13 servo motors SG90.
 * Ultrasonic sensor.
 * MPU-6050 3 Axis Acceleration + Gyroscope / 6 Axis Attitude Module.
 * Raspberry Pi 2.0. (Optional for controll it manually)
 
 ## Firmware
 * spidyfirmware

## Things to do
**Hardware**
  * Implement the 16 channels pwm controller.
  
**Software**
  * Create new code for using the previous hardware.

## Contributors

- [Sxubach](https://github.com/sxubach)
  - He will create the communication between a PC, the Raspberry Pi 3.0 and Arduino MEGA. 

- [didix21](https://github.com/didix21)
  - Build the robot and the Hardware and implement it with a firmware that will allow to control the servos, obtain IMU's and Ultrasonics sensor data.

- [XMabbX](https://github.com/XMabbX)
  - Investigate about the algorithm which will allow the robot to learn to walk and prepare for the next step of the project.
