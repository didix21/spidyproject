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
  static int state_send=0, option=0;

  static uint8_t legs_Angle[12] = {L1S1_REST, L1S2_REST,L2S1_REST, L2S2_REST, L3S1_REST, L3S2_REST, L4S1_REST, L4S2_REST, L5S1_REST, L5S2_REST, L6S1_REST, L6S2_REST};// {1,2,3,4,5,6,7,8,9,10,11,12};//
  static uint8_t current_legs_Angle[12] = {1,2,3,4,5,6,7,8,9,10,11,12};//
  static unsigned int duration_U=42;
 

  void receiveData(int byteCount);
  void sendData();

  void init_comunication()
  {
    Wire.begin(SLAVE_ADDRESS);  // initialize i2c as slave 
    
    Wire.onReceive(receiveData);  // define callbacks for i2c communication
    Wire.onRequest(sendData);   

    duration_U = 42;
  }

  void read_angles(uint8_t *legsAngle){
    for (int i=0;i<12;i++){
      legsAngle[i] = legs_Angle[i];
    }
  }

  void set_current_angles(uint8_t *legsAngle){
    for (int i=0;i<12;i++){
      current_legs_Angle[i] = legsAngle[i];
    }
  }

  void write_duration_U(unsigned int durationUltrasound){
    duration_U = durationUltrasound;
  }
     
  // callback for received data
  void receiveData(int byteCount){
    int i2c_option=0;
    while(Wire.available()) {     
      switch (state_receive){
        case 0:
          state_receive = Wire.read();

          #ifdef DEBUGGER          
            Serial.print("Request received: ");
            Serial.println(state_receive);          
          #endif
  
          if (state_receive>99){
            option = state_receive - 100;
            state_receive = 0;          
          }
        break;        
        case 1 ... 12:
          legs_Angle[state_receive-1] = Wire.read();          
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
    static byte buf[4];

    switch (state_send){
      case 0:     // Save current distance in the buffer and send firts part
        #ifdef DEBUGGER          
          Serial.print(" - Sending data:");
        #endif
        
        // to reconstruct
        // long value = (unsigned long)(buf[4] << 24) | (buf[3] << 16) | (buf[2] << 8) | buf[1];
        switch(option){
          case 0:
            buf[0] = (byte) duration_U;
            buf[1] = (byte) (duration_U >> 8);
            
            Wire.write(buf[0]);
            state_send = 1;
            
            #ifdef DEBUGGER            
              Serial.println(duration_U);
            #endif            
          break;
          case 1 ... 12:
            Wire.write(current_legs_Angle[option-1]); 
            
            #ifdef DEBUGGER         
              Serial.print("current pwm");   
              Serial.println(current_legs_Angle[option-1]);
            #endif            
          break;
          option = 0;
        }        
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


