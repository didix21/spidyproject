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
     * Public variables
     */
     public:
      Servo l1s1, l1s2, l2s1, l2s2, l3s1, l3s2, \
            l4s1, l4s2, l5s1, l5s2, l6s1, l6s2;
    /**
     * Public Methods
     */
    public:
      Spidy();
      void setSpidyRest();
      void setSpidyUp();
      void setSpidyDown();
      void refreshLegs(uint8_t *legsAngle);
      uint8_t readLegsPosition(uint8_t *legsAngle);
      bool checkPosition(uint8_t *legsAngle, uint8_t *legsPosition);
        
  };

#endif _SPIDY_H_
