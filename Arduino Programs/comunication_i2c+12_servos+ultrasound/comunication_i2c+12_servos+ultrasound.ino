// I2C definition
#include <Wire.h>
    
#define SLAVE_ADDRESS 0x04
int state_receive = 0;
int state_send=0,option;

// PWM definition
const int PWM_0 = 0;
const int PWM_1 = 1;
const int PWM_2 = 2;
const int PWM_3 = 3;
const int PWM_4 = 4;
const int PWM_5 = 5;
const int PWM_6 = 6;
const int PWM_7 = 7;
const int PWM_8 = 8;
const int PWM_9 = 9;
const int PWM_10 = 10;
const int PWM_11 = 11;
int pwm_values[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

// Ultrasound definition
const int TrigerPin = 7;  //Trigger pin of HC-SR04
const int listenPin = 8;  //Echo pin of HC-SR04
long duration_U, cm_U;
long accelerometer_X, accelerometer_Y, accelerometer_Z;

void define_pins_PWM();
void set_PWM();
long get_distance_U();

void setup() {
  Serial.begin(9600);         // start serial for output
  
  // I2C setup
  define_pins_PWM();
  Wire.begin(SLAVE_ADDRESS);  // initialize i2c as slave 

  Wire.onReceive(receiveData);  // define callbacks for i2c communication
  Wire.onRequest(sendData);     //

  // Ultrasound setup
  pinMode(listenPin, INPUT);
  pinMode(TrigerPin, OUTPUT);
  
  Serial.println("Ready!");
}
   
void loop() {
  set_PWM();
  cm_U = get_distance_U();
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

void define_pins_PWM(){
  pinMode(PWM_0, OUTPUT);
  pinMode(PWM_1, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  pinMode(PWM_3, OUTPUT);
  pinMode(PWM_4, OUTPUT);
  pinMode(PWM_5, OUTPUT);
  pinMode(PWM_6, OUTPUT);
  pinMode(PWM_7, OUTPUT);
  pinMode(PWM_8, OUTPUT);
  pinMode(PWM_9, OUTPUT);
  pinMode(PWM_10, OUTPUT);
  pinMode(PWM_11, OUTPUT);
}

// Function to update the value of the PWM in each servo
void set_PWM(){
  analogWrite(PWM_0, pwm_values[0]);
  analogWrite(PWM_1, pwm_values[1]);
  analogWrite(PWM_2, pwm_values[2]);
  analogWrite(PWM_3, pwm_values[3]);
  analogWrite(PWM_4, pwm_values[4]);
  analogWrite(PWM_5, pwm_values[5]);
  analogWrite(PWM_6, pwm_values[6]);
  analogWrite(PWM_7, pwm_values[7]);
  analogWrite(PWM_8, pwm_values[8]);
  analogWrite(PWM_9, pwm_values[9]);
  analogWrite(PWM_10, pwm_values[10]);
  analogWrite(PWM_11, pwm_values[11]);
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
  return cm_U;
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}


/*/ callback for sending data
void sendData(){
  byte buf[4];
  switch (state_send){
    case 0:     // Save current distance in the buffer and send firts part
      // to reconstruct
      // long value = (unsigned long)(buf[4] << 24) | (buf[3] << 16) | (buf[2] << 8) | buf[1];
      buf[0] = (byte) cm_U;
      buf[1] = (byte) cm_U >> 8;
      buf[2] = (byte) cm_U >> 16;
      buf[3] = (byte) cm_U >> 24;
      Wire.write(buf[0]);
      state_send = 1;
    break;
    case 1:
      Wire.write(buf[1]); 
      state_send = 2;    
    break;
    case 2:
      Wire.write(buf[2]);   
      state_send = 3;   
    break;    
    case 3:
      Wire.write(buf[3]);   
      state_send = 4;   
    break;    
    default:    
      state_send = 0;
    break;
  }
}*/



