
#include "SpidyPCA.cpp"

SpidyPCA::SpidyPCA() {

  
}

void SpidyPCA::wireConfiguration()
{
  Wire.begin();
  Wire.setClock(WIRE_BAUDRATE); 
}

void SpidyPCA::pcaConfig()
{
  pwmController.resetDevices();
  pwmController.init(I2C_ADDRESS);
}

