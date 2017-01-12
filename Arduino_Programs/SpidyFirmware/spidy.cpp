#include "spidy.h"
  
  /** 
   *  Constructor
   */
  Spidy::Spidy() {
       // Nothing
  }

  void Spidy::attachServos() {
       // Initialize Servo Motors
    l1s1.attach(L1S1_PIN);
    l1s2.attach(L1S2_PIN);
    l2s1.attach(L2S1_PIN);
    l2s2.attach(L2S2_PIN);
    l3s1.attach(L3S1_PIN);
    l3s2.attach(L3S2_PIN);
    l4s1.attach(L4S1_PIN);
    l4s2.attach(L4S2_PIN);
    l5s1.attach(L5S1_PIN);
    l5s2.attach(L5S2_PIN);
    l6s1.attach(L6S1_PIN);
    l6s2.attach(L6S2_PIN); 
    
  }

  /** 
   * Sent all the servos to rest  
   */
  void Spidy::setSpidyRest() {
    
    l1s1.write(L1S1_REST);
    l1s2.write(L1S2_REST);
    l2s1.write(L2S1_REST);
    l2s2.write(L2S2_REST);
    l3s1.write(L3S1_REST);
    l3s2.write(L3S2_REST);
    l4s1.write(L4S1_REST);
    l4s2.write(L4S2_REST);
    l5s1.write(L5S1_REST);
    l5s2.write(L5S2_REST);
    l6s1.write(L6S1_REST);
    l6s2.write(L6S2_REST);
    
   }

   /** 
    * To rise Spidy 
    */
   void Spidy::setSpidyUp() {
    
    l1s2.write(L1S2_MAX);
    l2s2.write(L2S2_MAX);
    l3s2.write(L3S2_MAX);
    l4s2.write(L4S2_MAX);
    l5s2.write(L5S2_MAX);
    l6s2.write(L6S2_MAX);
    
   }

  /** 
   * Set down Spidy
   */
   void Spidy::setSpidyDown() {
    
    l1s2.write(L1S2_MIN);
    l2s2.write(L2S2_MIN);
    l3s2.write(L3S2_MIN);
    l4s2.write(L4S2_MIN);
    l5s2.write(L5S2_MIN);
    l6s2.write(L6S2_MIN);
  
   }

  /**
   * This function is in charge of refresh all the servo legs.
   * Possible some time delays will be implemented in futur to 
   * avoid high inductances and Arduino Saturation.
   */
   void Spidy::refreshLegs(uint8_t *legsAngle) {

    // Actualize legs position
    l1s1.write(legsAngle[0]);
    l1s2.write(legsAngle[1]);
    l2s1.write(legsAngle[2]);
    l2s2.write(legsAngle[3]);
    l3s1.write(legsAngle[4]);
    l3s2.write(legsAngle[5]);
    l4s1.write(legsAngle[6]);
    l4s2.write(legsAngle[7]);
    l5s1.write(legsAngle[8]);
    l5s2.write(legsAngle[9]);
    l6s1.write(legsAngle[10]);
    l6s2.write(legsAngle[11]);
    
   }

  /**
   * This function read all the actual servo values
   */
   uint8_t* Spidy::readLegsPosition(uint8_t *legsPosition) {
    
    //uint8_t legsPosition[12]; // Twelve Servo Motors
    
    // Read actual legs position
    legsPosition[0] = l1s1.read();
    legsPosition[1] = l1s2.read();
    legsPosition[2] = l2s1.read();
    legsPosition[3] = l2s2.read();
    legsPosition[4] = l3s1.read();
    legsPosition[5] = l3s2.read();
    legsPosition[6] = l4s1.read();
    legsPosition[7] = l4s2.read();
    legsPosition[8] = l5s1.read();
    legsPosition[9] = l5s2.read();
    legsPosition[10] = l6s1.read();
    legsPosition[11] = l6s2.read();

    return legsPosition;
   }
   
   /**
    * CheckPostion: checks if all the servo have reached the goal values.
    */
   bool* Spidy::checkPosition(uint8_t *legsAngle, uint8_t *legsPosition) {
    
    bool achievedPosition[12]; // This array will be used to know if all the servos has achieved the position
    
    // Check if servos has achieved the position desired
    for(int i = 0; i < 11; i++) {
      // (legsAngle[i] - 10) <= legsPosition[i] <= (legsAngle[i] + 10)
      if((legsPosition[i] >= (legsAngle[i] - 10)) && (legsPosition[i] <= (legsAngle[i] + 10))) { 
        achievedPosition[i] = true;
      } 
      else {
        achievedPosition[i] = false;
      }
    }

    return achievedPosition;
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
   
