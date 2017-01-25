/**
 * Declaration of Spidy Class
 */

#ifndef _SPIDY_H_

  #define _SPIDY_H_
  #include "Arduino.h"
  #include <Servo.h>
  #include "configuration.h"
  
  
  class Spidy {

      
    /**
     * Public Methods
     */
    public:
      Spidy(); 
      void attachServos();
      void setSpidyRest();
      void setSpidyUp();
      void setSpidyDown();
      void refreshLegs(uint8_t *legsAngle);
      void checkInsideMinMax(uint8_t *legsAngle);
      void readLegsPosition(uint8_t *legsAngle);
      bool* checkPosition(uint8_t *legsAngle, uint8_t *legsPosition);

      
    /**
     * Public variables
     */
    public:
      Servo l1s1, l1s2, l2s1, l2s2, l3s1, l3s2, \
            l4s1, l4s2, l5s1, l5s2, l6s1, l6s2;  
            
    /**
     * Private Variables
     */
     private:
       uint8_t minPos[12]={L1S1_MIN,L1S2_MIN,L2S1_MIN,L2S2_MIN,L3S1_MIN,L3S2_MIN, \
                            L4S1_MIN,L4S2_MIN,L5S1_MIN,L5S2_MIN,L6S1_MIN,L6S2_MIN};
       uint8_t maxPos[12]={L1S1_MAX,L1S2_MAX,L2S1_MAX,L2S2_MAX,L3S1_MAX,L3S2_MAX, \
                            L4S1_MAX,L4S2_MAX,L5S1_MAX,L5S2_MAX,L6S1_MAX,L6S2_MAX};
   
  };

#endif _SPIDY_H_
