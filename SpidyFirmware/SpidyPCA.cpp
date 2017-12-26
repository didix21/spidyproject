
#ifdef PCA9685_BOARD


  #include "SpidyPCA.h"
  
  
  SpidyPCA::SpidyPCA() {
  
    wireConfiguration(); // Starts Wire connection.
    pcaConfig(); // Configurates the PCA9685.
  
  }
  
  /**
  * @wireConfiguration: starts wire connection, must be started before
  * configurate the PCA9685 board.
  */
  void SpidyPCA::wireConfiguration()
  {
    Wire.begin();
    Wire.setClock(WIRE_BAUDRATE); // Supported baud rates are 100 kHz, 400 kHz, and 1000 kHz
  }
  
  void SpidyPCA::pcaConfig()
  {
    pwmController.resetDevices();   // Software resets all PCA9685 devices on Wire line
    pwmController.init(I2C_ADDRESS);// Default is 200 Hz, supports 24 Hz to 1526 Hz
  }
  
  void SpidyPCA::setSpidyRest()
  {
    uint8_t servo_values = {L1S1_REST, L1S2_REST, L2S1_REST, L2S2_REST, L3S1_REST, L3S2_REST, \
                            L4S1_REST, L4S2_REST, L5S1_REST, L5S2_REST, L6S1_REST, L6S2_REST};
    for(uint8_t i = 0, i < 12, i++)
      pwmController.setChannelPWM(i, servos.pwmForAngle(servo_values[i]));
  }
  
  void SpidyPCA::setSpidyUp()
  {
    uint8_t servo_values = {L1S2_MAX, L2S2_MAX, L3S2_MAX, L4S2_MAX, L5S2_MAX, L6S2_MAX};
    uint8_t j = 0;
    for(uint8_t i = 1; i < 12; i+2)
    {
      pwmController.setChannelPWM(i, servos.pwmForAngle(servo_values[j]));
      j++;
    }
  }
  
  void SpidyPCA::setSpidyDown()
  {
    uint8_t servo_values = {L1S2_MIN, L2S2_MIN, L3S2_MIN, L4S2_MIN, L5S2_MIN, L6S2_MIN};
    uint8_t j = 0;
    for(uint8_t i = 1; i < 12; i+2)
    {
      pwmController.setChannelPWM(i, servos.pwmForAngle(servo_values[j]));
      j++;
    }
  }
  
  void SpidyPCA::refreshLegs(uint8_t *legsAngle)
  {
    for(uint8_t i = 0; i < 12; i++)
      pwmController.setChannelPWM(i, servos.pwmForAngle(legsAngle[i]));
  }

  #endif // PCA9685_BOARD
