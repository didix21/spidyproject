
/*
This file Reads from the Ultrasound and Accelerometer and allows to controls de PWM through i2c from a master.
In:   -12 x PWM (1st request the number of pwm to controll / 2nd request pwm value)
Out:  -ultrasound (1st request 100 to select ultrasound / 2nd read 8 LSB of the value / 3rd read 2 MSB of the value)
  -accelerometer (1st request 101..103 for XYZ respectively / 2nd read 8 LSB of the value / 3rd read 2 MSB of the value)
*/


// I2C definition
#include <Wire.h>
    
#define SLAVE_ADDRESS 0x04
int state_receive = 0;
int state_send=0,option;

// PWM definition
int pwm_values[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

// Ultrasound definition
const int TrigerPin = 7;  //Trigger pin of HC-SR04
const int listenPin = 8;  //Echo pin of HC-SR04
long duration_U, cm_U;
long accelerometer_X, accelerometer_Y, accelerometer_Z;


long get_distance_U();

void setup() {
  Serial.begin(9600);         // start serial for output
  
  // I2C setup
  Wire.begin(SLAVE_ADDRESS);  // initialize i2c as slave 

  Wire.onReceive(receiveData);  // define callbacks for i2c communication
  Wire.onRequest(sendData);     //

  // Ultrasound setup
  pinMode(listenPin, INPUT);
  pinMode(TrigerPin, OUTPUT);
  
  Serial.println("Ready!");
}
   
void loop() {
  get_distance_U();
  delay(100);
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

// Get distance from the ultrasound sensor
long get_distance_U(){
  digitalWrite(TrigerPin, LOW);    //securing 0 in trigger pin
  delayMicroseconds(2);            //for 2 us
  digitalWrite(TrigerPin, HIGH);   //fixing 1 in trigger pin
  delayMicroseconds(5);            //for 5 us
  digitalWrite(TrigerPin, LOW);    //fixing 0 back

  duration_U = pulseIn(listenPin, HIGH);    //save valor of time echo takes to come
  cm_U = microsecondsToCentimeters(duration_U); //changes s to m

  Serial.print(cm_U);
  Serial.print("cm");
  Serial.println();  
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}



