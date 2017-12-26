
#ifdef PCA9685_BOARD

#ifndef _SPIDYPCA_H_
  #define _SPIDY_PCA_H_


  #include <Wire.h>
  #include "PCA9685.h"

  class SpidyPCA {

    public:
      SpidyPCA();
      void wireConfiguration(); // Configures the Wire.
      void pcaConfig();         // Configurates the PCA.
      void setSpidyRest();
      void setSpidyUp();
      void setSpidyDown();
      void refreshLegs(uint8_t *legsAngle);


    public:
      PCA9685 pwmController;
      PCA9685_ServoEvaluator servos;
  };


#endif // _SPIDYPCA_H_

#endif // PCA9685_BOARD
