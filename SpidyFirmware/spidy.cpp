#include "spidy.h"
  
  /** 
   * Sent all the servos to rest  
   */
  void Spidy::setSpidyRest() {
    
    #ifdef ARDUINO_MEGA
    
      spidymega.setSpidyRest();

    #endif
    
   }

   /** 
    * To rise Spidy 
    */
   void Spidy::setSpidyUp() {

    #ifdef ARDUINO_MEGA
    
      spidymega.setSpidyUp();

    #endif
    
   }

  /** 
   * Set Spidy down
   */
   void Spidy::setSpidyDown() {

    #ifdef ARDUINO_MEGA
    
      spidymega.setSpidyDown();

    #endif

   }

  /**
   * This function is in charge of refresh all the servo legs.
   * Possible some time delays will be implemented in futur to 
   * avoid high inductances and Arduino Saturation.
   */
   void Spidy::refreshLegs(uint8_t *legsAngle) {

    #ifdef ARDUINO_MEGA
    
      spidymega.refreshLegs(legsAngle); // Update legs position using Servo library.

    #endif
    
   }

  /**
   * This function read all the actual servo values
   */
   void Spidy::readLegsPosition(uint8_t *legsPosition) {
    
    #ifdef ARDUINO_MEGA   
      
      spidymega.readLegsPosition(legsPosition); // Read actual legs position using Servo library

    #endif
    
   }
   
   /**
    * CheckPostion: checks if all the servo have reached the goal values.
    */
   bool *Spidy::checkPosition(uint8_t *legsAngle, uint8_t *legsPosition) {
    
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
   void Spidy::checkInsideMinMax(uint8_t *legsAngle) {
    
    int i;
    for(i = 0; i < 11; i++) {
      if(legsAngle[i] < minPos[i]) legsAngle[i] = minPos[i];
      else if(legsAngle[i] > maxPos[i]) legsAngle[i] = maxPos[i];
    }   
   }
   
