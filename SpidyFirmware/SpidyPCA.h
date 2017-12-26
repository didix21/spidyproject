


#ifndef _SPIDYPCA_H_
  #define _SPIDY_PCA_H_

  #include "configuration.h"
  #include <Wire.h>
  #include "PCA9685.h"

  class SpidyPCA {

    public:
      SpidyPCA() {}
      void wireConfiguration(uint8_t wire_baudrate); // Configures the Wire.
      void pcaConfiguration(byte i2c_address);         // Configurates the PCA.
      void setSpidyRest();
      void setSpidyUp();
      void setSpidyDown();
      void refreshLegs(uint8_t *legsAngle);
      void refreshOneLeg(char leg, int legAngle);


    public:
      PCA9685 pwmController;
      PCA9685_ServoEvaluator servos;
  };


#endif // _SPIDYPCA_H_


