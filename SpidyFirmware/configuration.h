/**
 * This File contains all the numeret PINS needed and the servo configurations range
 */

#ifndef _CONFIGURATION_H_

  #define _CONFIGURATION_H_
  
 /**
  * L = Leg, Nº is the leg number.
  * S = Servo, Nº is the servo number: 1 is the servo near the paw and 2 is the base servo
  */

  /********************* SPIDY ********************
   *                                              *
   *                                              *
   *                     POWER                    *
   *                     -   +                    *
   *                     |   |                    *
   *       ________________________________       *
   *      |                                |      *
   * L6S2 | L6S1                      L5S1 | L5S2 *
   *      |                                |      *
   *      |                                |      *
   *      |                                |      *
   *      |                                |      *
   *      |                                |      *
   * L4S2 |  L4S1                     L3S1 | L3S2 *
   *      |                                |      *
   *      |                                |      *
   *      |                                |      *
   *      |                                |      *
   *      |                                |      *
   * L2S2 | L2S1                      L1S1 | L1S2 *
   *      |________________________________|      *
   *                    |     |                   *
   *                    |     |                   *
   *                    -------                   *
   *                      USB                     * 
   *                                              *
   ************************************************                      
   */
   
// ************************************ BOARDS ***********************************
// Uncomment this board that you are using in order to control spidy.
  
  //#define ARDUINO_MEGA // Uncomment this line if you are using an arduino Mega to control 
                         // the servo motors.   
  #define PCA9685_BOARD // Uncomment this if the spidy works with the PCA9685
// ***********************************************************************************
                       
// ************************************ SERVO PINS ***********************************

#ifdef ARDUINO_MEGA
                
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

#endif // ARDUINO_MEGA
  // ***********************************************************************************
  
  // Debugger mode 

  #define DEBUGGER // If the define is not commented, the debugger mode is set

  
  #ifdef PCA9685_BOARD
    
    #define WIRE_BAUDRATE 400000    // Supported baud rates are 100kHz, 400kHz, and 1000kHz
    #define I2C_ADDRESS B000000     // Address pins A5-A0 set to B000000
    #define PWM_FREQUENCY 50        // 50Hz provides 20ms standard servo phase length

  #endif
  
 // Serial Definition
 #ifndef MYSERESIAL
 
  #define MYSERIAL Serial // Usefull for MEGA we can change easily between Serial, Serial1, Serial2

  #ifndef BAUDRATE

    #define BAUDRATE 115200

  #endif

  #define COMMANDLINE_CONTROL // Uncomment this if you want to use command line to control spidy robot.
 
 #endif // MYSER

// *********************************** Range of each servo leg ***********************************
/**
 * The following variables configures the minimun and maximum range of each servo motor using
 * Arduino MEGA.
 */
#ifdef ARDUINO_MEGA
 #ifndef RANGE_OF_EACH_SERVO // 
  
  // Leg 1 
  #define L1S1_MIN 0  // In degrees
  #define L1S1_MAX 110 // In degrees
  #define L1S2_MIN 100 // In degrees
  #define L1S2_MAX 180 // In degrees
  // Leg 2
  #define L2S1_MIN 50 // In degrees
  #define L2S1_MAX 170 // In degrees
  #define L2S2_MIN 5 // In degrees
  #define L2S2_MAX 110 // In degrees
  // Leg 3
  #define L3S1_MIN 0 // In degrees
  #define L3S1_MAX 100 // In degrees
  #define L3S2_MIN 30 // In degrees
  #define L3S2_MAX 120 // In degrees
  // Leg 4
  #define L4S1_MIN 15 // In degrees
  #define L4S1_MAX 100 // In degrees
  #define L4S2_MIN 25 // In degrees
  #define L4S2_MAX 100 // In degrees
  // Leg 5
  #define L5S1_MIN 5 // In degrees
  #define L5S1_MAX 150 // In degrees
  #define L5S2_MIN 0 // In degrees
  #define L5S2_MAX 100 // In degrees
  // Leg 6
  #define L6S1_MIN 25 // In degrees
  #define L6S1_MAX 180 // In degrees
  #define L6S2_MIN 20 // In degrees
  #define L6S2_MAX 110 // In degrees

  // Centrate Base Paws
  #define L1S1_REST 50 //(L1S1_MAX - L1S1_MIN)/2
  #define L1S2_REST L1S2_MIN//(L1S2_MAX - L1S2_MIN)/2   //90
  #define L2S1_REST 110 //(L2S1_MAX - L2S1_MIN)/2
  #define L2S2_REST L2S2_MIN//(L2S2_MAX - L2S2_MIN)/2   //5
  
  #define L3S1_REST 50//(L3S1_MAX - L3S1_MIN)/2
  #define L3S2_REST L3S2_MIN//(L3S2_MAX - L3S2_MIN)/2   //30
  #define L4S1_REST 55//(L4S1_MAX - L4S1_MIN)/2
  #define L4S2_REST L4S2_MIN//(L4S2_MAX - L4S2_MIN)/2   //20
  
  #define L5S1_REST 60//(L5S1_MAX - L5S1_MIN)/2
  #define L5S2_REST L5S2_MIN//(L5S2_MAX - L5S2_MIN)/2   //0
  #define L6S1_REST 120   //(L6S1_MAX - L6S1_MIN)/2
  #define L6S2_REST L6S2_MIN//(L1S2_MAX - L6S2_MIN)/2   //60
                     
  #define RANGE_OF_EACH_SERVO

 #endif // RANGE_OF_EACH_SERVO
 #endif //ARDUINO_MEGA

#ifdef PCA9685_BOARD
  #ifndef RANGE_OF_EACH_SERVO // 
  
  // Leg 1 
  #define L1S1_MIN -70  // In degrees
  #define L1S1_MAX 40 // In degrees
  #define L1S2_MIN -85 // In degrees
  #define L1S2_MAX 0 // In degrees
  // Leg 2
  #define L2S1_MIN -40 // In degrees
  #define L2S1_MAX 70 // In degrees
  #define L2S2_MIN -70 // In degrees
  #define L2S2_MAX 10 // In degrees
  // Leg 3
  #define L3S1_MIN -75 // In degrees
  #define L3S1_MAX -10 // In degrees
  #define L3S2_MIN -50 // In degrees
  #define L3S2_MAX 35 // In degrees
  // Leg 4
  #define L4S1_MIN -55 // In degrees
  #define L4S1_MAX 10 // In degrees
  #define L4S2_MIN -65 // In degrees
  #define L4S2_MAX 10 // In degrees
  // Leg 5
  #define L5S1_MIN -90// In degrees
  #define L5S1_MAX -10 // In degrees
  #define L5S2_MIN 10 // In degrees
  #define L5S2_MAX 90 // In degrees
  // Leg 6
  #define L6S1_MIN -10 // In degrees
  #define L6S1_MAX 90 // In degrees
  #define L6S2_MIN -70 // In degrees
  #define L6S2_MAX 40 // In degrees

  // Centrate Base Paws
  #define L1S1_REST -30 //(L1S1_MAX - L1S1_MIN)/2
  #define L1S2_REST L1S2_MIN//(L1S2_MAX - L1S2_MIN)/2   //90
  #define L2S1_REST 40 //(L2S1_MAX - L2S1_MIN)/2
  #define L2S2_REST L2S2_MIN//(L2S2_MAX - L2S2_MIN)/2   //5
  
  #define L3S1_REST -45//(L3S1_MAX - L3S1_MIN)/2
  #define L3S2_REST L3S2_MIN//(L3S2_MAX - L3S2_MIN)/2   //30
  #define L4S1_REST -30//(L4S1_MAX - L4S1_MIN)/2
  #define L4S2_REST L4S2_MIN//(L4S2_MAX - L4S2_MIN)/2   //20
  
  #define L5S1_REST -40//(L5S1_MAX - L5S1_MIN)/2
  #define L5S2_REST L5S2_MIN//(L5S2_MAX - L5S2_MIN)/2   //0
  #define L6S1_REST 25   //(L6S1_MAX - L6S1_MIN)/2
  #define L6S2_REST L6S2_MIN//(L1S2_MAX - L6S2_MIN)/2   //60
                     
  #define RANGE_OF_EACH_SERVO

 #endif // RANGE_OF_EACH_SERVO
#endif // PCA9685_BOARD
// **************************************************************************************************

#endif // _CONFIGURATION_H_
