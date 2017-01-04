#include "main.h"


void setup() {
  // put your setup code here, to run once:
  MYSERIAL.begin(BAUDRATE);
  if(MYSERIAL.available()){
    MYSERIAL.println(ASTERISKS);
    MYSERIAL.println(SPIDY_FIRMWARE);
    MYSERIAL.println(ASTERISKS);
  }
  spidy.attachServos();
  
  init_comunication();
  ultrasound_setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  commandLine();
  
  update_duration_U();
  read_angles(legsAngle);
  
  spidy.refreshLegs(legsAngle);


  Serial.print("Distance_U = ");
  Serial.println(duration_U);
  Serial.print("pwm = [");
  Serial.print(legsAngle[0]);
  for (int i=1;i<12;i++){
    Serial.print(", ");
    Serial.print(legsAngle[i]);
  }
  Serial.println("]");
  delay(50);
}

   void serialEvent(){
      while(MYSERIAL.available()) {
        data=(char)MYSERIAL.read();    
        if (data != '\n'){
          syllable[i++]=data;   
        } else{
           MYSERIAL.println("Read Event Finished");
           comFinished = true; 
           x=i;
           i=0;
        }
      }
   }
