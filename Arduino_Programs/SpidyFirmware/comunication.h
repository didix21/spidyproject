/**
 * ultrasound.h
 */

#ifndef _COMUNICATION_H_
  #define _COMUNICATION_H_

  #include <Wire.h>
  
  #define SLAVE_ADDRESS 0x04
  
  int state_receive;
  int state_send, option;
  int pwm_values[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  long duration_U, cm_U;
  long accelerometer_X, accelerometer_Y, accelerometer_Z;

  void receiveData(int byteCount);
  void sendData();

  void init_comunication()
  {
    Wire.begin(SLAVE_ADDRESS);  // initialize i2c as slave 
    
    Wire.onReceive(receiveData);  // define callbacks for i2c communication
    Wire.onRequest(sendData);   
    
    //initialize state machines
    state_receive = 0;
    state_send=0;
    
    // Set initial values
    duration_U = 0;
  }
     
  // callback for received data
  void receiveData(int byteCount){
    int i2c_option=0;
    while(Wire.available()) {    
      switch (state_receive){
        case 0:
          state_receive = Wire.read();
          Serial.print("data received: info about PWM_");
          Serial.println(state_receive);
  
          if (state_receive>99){
            option = state_receive - 100;
            state_receive = 0;          
          }
        break;        
        case 1 ... 12:
          pwm_values[state_receive-1] = Wire.read();
          Serial.print("data received: ");
          Serial.println(pwm_values[state_receive-1]);
          state_receive = 0;
        break;
        default:
          state_receive = 0;
        break;      
      }
    }
  }

  // callback for sending data
  void sendData(){ //otpion: 0=ultrasound 1=accelerometer_X 2=accelerometer_Y 3=accelerometer_Z
    byte buf[4];
  
    switch (state_send){
      case 0:     // Save current distance in the buffer and send firts part
        // to reconstruct
        // long value = (unsigned long)(buf[4] << 24) | (buf[3] << 16) | (buf[2] << 8) | buf[1];
        switch(option){
          case 0:
            buf[0] = (byte) duration_U;
            buf[1] = (byte) duration_U >> 8;
          break;
          case 1:
            buf[0] = (byte) accelerometer_X;
            buf[1] = (byte) accelerometer_X >> 8;
          break;
          case 2:
            buf[0] = (byte) accelerometer_Y;
            buf[1] = (byte) accelerometer_Y >> 8;
          break;
          case 3:
            buf[0] = (byte) accelerometer_Z;
            buf[1] = (byte) accelerometer_Z >> 8;
          break;
          default:
            option = 0;
          break;
        }
        
        Wire.write(buf[0]);
        state_send = 1;
      break;
      case 1:
        Wire.write(buf[1]); 
        state_send = 0;    
      break;
      default:    
        state_send = 0;
      break;
    }
  }


#endif // _COMUNICATION_H_


