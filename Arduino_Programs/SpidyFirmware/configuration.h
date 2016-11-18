/**
 * This File contains all the numeret PINS needed and the servo configurations range
 */

#ifndef _CONFIGURATION_H_

  #define _CONFIGURATION_H_
  
 /**
  * L = Leg, Nº is the leg number.
  * S = Servo, Nº is the servo number: 1 is the servo near the paw and 2 is the base servo
  */
  // *********************************** SERVO PINS ***********************************
  #ifndef LNSN    
  
   #define L1S1_PIN 13   // Leg 1 Servo 1
   #define L1S2_PIN 12   // Leg 1 Servo 2
   #define L2S1_PIN 11   // Leg 2 Servo 1
   #define L2S2_PIN 10   // Leg 2 Servo 2
   #define L3S1_PIN 9   // Leg 3 Servo 1
   #define L3S2_PIN 8   // Leg 3 Servo 2
   #define L4S1_PIN 7   // Leg 4 Servo 1 
   #define L4S2_PIN 6  // Leg 4 Servo 2
   #define L5S1_PIN 5  // Leg 5 Servo 1
   #define L5S2_PIN 4  // Leg 5 Servo 2
   #define L6S1_PIN 3  // Leg 6 Servo 1
   #define L6S2_PIN 2  // Leg 6 Servo 2
  
  #endif // LNSN
  // ***********************************************************************************
  
  
 // Serial Definition
 #ifndef MYSERESIAL
 
  #define MYSERIAL Serial // Usefull for MEGA we can change easily between Serial, Serial1, Serial2

  #ifndef BAUDRATE

    #define BAUDRATE 9600

  #endif

  #define COMMANDLINE_CONTROL // Uncomment this if you want to use command line to control spidy robot.
 
 #endif // MYSER

// *********************************** Range of each servo leg ***********************************

 #ifndef RANGE_OF_EACH_SERVO // 
  
  // Leg 1 
  #define L1S1_MIN 0  // In degrees
  #define L1S1_MAX 180 // In degrees
  #define L1S2_MIN 90 // In degrees
  #define L1S2_MAX 90 // In degrees
  // Leg 2
  #define L2S1_MIN 0 // In degrees
  #define L2S1_MAX 180 // In degrees
  #define L2S2_MIN 90 // In degrees
  #define L2S2_MAX 90 // In degrees
  // Leg 3
  #define L3S1_MIN 0 // In degrees
  #define L3S1_MAX 180 // In degrees
  #define L3S2_MIN 90 // In degrees
  #define L3S2_MAX 90 // In degrees
  // Leg 4
  #define L4S1_MIN 0 // In degrees
  #define L4S1_MAX 180 // In degrees
  #define L4S2_MIN 90 // In degrees
  #define L4S2_MAX 90 // In degrees
  // Leg 5
  #define L5S1_MIN 0  // In degrees
  #define L5S1_MAX 180 // In degrees
  #define L5S2_MIN 90 // In degrees
  #define L5S2_MAX 90 // In degrees
  // Leg 6
  #define L6S1_MIN 0 // In degrees
  #define L6S1_MAX 180 // In degrees
  #define L6S2_MIN 90 // In degrees
  #define L6S2_MAX 90 // In degrees

  // Centrate Base Paws
  #define L1S2_REST (L1S2_MAX - L1S2_MIN)/2
  #define L2S2_REST (L2S2_MAX - L2S2_MIN)/2
  #define L3S2_REST (L3S2_MAX - L3S2_MIN)/2
  #define L4S2_REST (L4S2_MAX - L4S2_MIN)/2
  #define L5S2_REST (L5S2_MAX - L5S2_MIN)/2
  #define L6S2_REST (L1S2_MAX - L6S2_MIN)/2
                     
  #define RANGE_OF_EACH_SERVO

 #endif // RANGE_OF_EACH_SERVO

// **************************************************************************************************

#endif // _CONFIGURATION_H_
