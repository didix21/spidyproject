
#ifdef ARDUINO_MEGA

/**
 * Declaration of Spidy Class
 */

#ifndef _SPIDYMEGA_H_
  #define _SPIDYMEGA_H_

  #include "Arduino.h"
  #include <Servo.h>
  #include "configuration.h"


  class SpidyMEGA {


    /**
     * Public Methods
     */
    public:
      SpidyMEGA();
      void attachServos();
      void setSpidyRest();
      void setSpidyUp();
      void setSpidyDown();
      void refreshLegs(uint8_t *legsAngle);
      void checkInsideMinMax(uint8_t *legsAngle);
      void readLegsPosition(uint8_t *legsAngle);

    /**
     * Public variables
     */
    public:
      Servo l1s1, l1s2, l2s1, l2s2, l3s1, l3s2, \
            l4s1, l4s2, l5s1, l5s2, l6s1, l6s2;


  };

#endif //_SPIDYMEGA_H_

#endif // ARDUINO_MEGA
