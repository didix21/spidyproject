#include "spidy.h"
  
  /** 
   * Sent all the servos to rest  
   */
  void Spidy::setSpidyRest() {
    
    #if defined(ARDUINO_MEGA)
    
      spidymega.setSpidyRest();

    #elif defined(PCA9685_BOARD)
    
      spidypca.setSpidyRest();
  
    #endif
    
   }

   /** 
    * To rise Spidy 
    */
   void Spidy::setSpidyUp() {

    #if defined(ARDUINO_MEGA)
    
      spidymega.setSpidyUp();
    
    #elif defined(PCA9685_BOARD)
    
      spidypca.setSpidyUp();
  
    #endif
    
   }

  /** 
   * Set Spidy down
   */
   void Spidy::setSpidyDown() {

    #if defined(ARDUINO_MEGA)
    
      spidymega.setSpidyDown();
      
    #elif defined(PCA9685_BOARD)
    
      spidypca.setSpidyDown();
  
    #endif

   }

  /**
   * This function is in charge of refresh all the servo legs.
   * Possible some time delays will be implemented in futur to 
   * avoid high inductances and Arduino Saturation.
   */
   void Spidy::refreshLegs(int *legsAngle) {

    #if defined(ARDUINO_MEGA)
    
      spidymega.refreshLegs(legsAngle); // Update legs position using Servo library.
    
    #elif defined(PCA9685_BOARD)
    
      //spidypca.refreshLegs(legsAngle);
  
    #endif
    
   }

  /**
   * This function read all the actual servo values
   */
   void Spidy::readLegsPosition(int *legsPosition) {
    
    #if defined(ARDUINO_MEGA)
      
      spidymega.readLegsPosition(legsPosition); // Read actual legs position using Servo library

    #elif defined(PCA9685_BOARD)

     // spidypca.readLegsPosition(legsPosition);

    #endif
    
   }
   
   /**
    * CheckPostion: checks if all the servo have reached the goal values.
    */
   bool *Spidy::checkPosition(int *legsAngle, int *legsPosition) {
    
    bool *checkArray = new bool[12]; // This array will be used to know if all the servos has achieved the position
    
    // Check if servos has achieved the position desired
    for(int i = 0; i < 11; i++) {
      // (legsAngle[i] - 10) <= legsPosition[i] <= (legsAngle[i] + 10)
      if((legsPosition[i] >= (legsAngle[i] - 10)) && (legsPosition[i] <= (legsAngle[i] + 10))) { 
        checkArray[i] = true;
      } 
      else {
        checkArray[i] = false;
      }
    }

    return checkArray; 
   }
   
   /**
    * checkInsideMinMax: check if each servo angle received is inside min max range.
    * This function avoids force the different servos.
    */
   void Spidy::checkInsideMinMax(int *legsAngle) {
    
    int i;
    for(i = 0; i < 11; i++) {
      if(legsAngle[i] < minPos[i]) legsAngle[i] = minPos[i];
      else if(legsAngle[i] > maxPos[i]) legsAngle[i] = maxPos[i];
    }   
   }
   
