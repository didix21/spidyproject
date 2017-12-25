#include "spidy.h"
  
  /** 
   *  Constructor
   */
  Spidy::Spidy() {
       // Nothing
  }


  /** 
   * Sent all the servos to rest  
   */
  void Spidy::setSpidyRest() {
    
    spidymega.setSpidyRest();
    
   }

   /** 
    * To rise Spidy 
    */
   void Spidy::setSpidyUp() {
    
    spidymega.setSpidyUp();
    
   }

  /** 
   * Set Spidy down
   */
   void Spidy::setSpidyDown() {

    spidymega.setSpidyDown();

   }

  /**
   * This function is in charge of refresh all the servo legs.
   * Possible some time delays will be implemented in futur to 
   * avoid high inductances and Arduino Saturation.
   */
   void Spidy::refreshLegs(uint8_t *legsAngle) {

    // Actualize legs position
    spidymega.refreshLegs(legsAngle);
    
   }

  /**
   * This function read all the actual servo values
   */
   void Spidy::readLegsPosition(uint8_t *legsPosition) {
       
    // Read actual legs position
    spidymega.readLegsPosition(legsPosition);

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
   
