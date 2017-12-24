


#ifndef _SPIDYPCA_H_
  #define _SPIDY_PCA_H_

  
  #include <Wire.h>
  #include "PCA9685.h"
  
  class SpidyPCA {
    
    public:
      void  wireConfiguration(); // Configures the Wire.
      void  pcaConfig();         // Configurates the PCA.

    public:
      PCA9685 pwmController;
      PCA9685_ServoEvaluator servos;
      
    
    
  };


#endif // _SPIDYPCA_H_

