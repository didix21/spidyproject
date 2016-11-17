/**
 * comunication.h
 * 
 *  Through a call to init_comunication() an i2c comunication will be setup useing the following protocol:
 *    On receive data request:
 *      -read number of leg [1..12] or option for send data: 100=ultrasound 101=accelerometer_X 102=accelerometer_Y 103=accelerometer_Z
 *      -read PWM duty cycle [0..255]
 *      
 *    On send data request:
 *      (requires an option selection from a receive data request)
 *      -send LSByte from the data asked for
 *      -send MSByte from the data asked for
 *      
 *  To update the values of the variables sent use the functions read_angles(), write_duration_U() and write_accelerometer()
 */

#ifndef _COMUNICATION_H_
  #define _COMUNICATION_H_

  #include <Wire.h>
  
  #define SLAVE_ADDRESS 0x04
  
  static int state_receive=0;
  static int state_send=0, option;

  static uint8_t legs_Angle[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  static unsigned int duration_U=0;
  static int accelerometer_X=0, accelerometer_Y=0, accelerometer_Z=0;
  

  void receiveData(int byteCount);
  void sendData();

  void init_comunication()
  {
    Wire.begin(SLAVE_ADDRESS);  // initialize i2c as slave 
    
    Wire.onReceive(receiveData);  // define callbacks for i2c communication
    Wire.onRequest(sendData);   
  }

  void read_angles(uint8_t *legsAngle){
    legsAngle = legs_Angle;
  }

  void write_duration_U(unsigned int durationUltrasound){
    duration_U = durationUltrasound;
  }

  void write_accelerometer(int acc_x, int acc_y, int acc_z){
    accelerometer_X = acc_x;
    accelerometer_Y = acc_y;
    accelerometer_Z = acc_z;
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
          legs_Angle[state_receive-1] = Wire.read();
          Serial.print("data received: ");
          Serial.println(legs_Angle[state_receive-1]);
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


