/**
 * Spidyfirmware was created by Sergi Xavier Ubach and Dídac Coll. This firmware it is created in order to
 * use with the robot spidy. The refernces can be found in: 
 */



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
  spidy.setSpidyRest();
  init_comunication();
  ultrasound_setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  #ifdef COMMANDLINE_CONTROL // Go to configuration and comment the #define COMMANDLINE_CONTROL
    
    commandLine();
    
  #else
    
    update_duration_U();
    read_angles(legsAngle);
    
    #ifdef DEBUGGER // Debugger in order to print via serial the errors
    
      Serial.println(duration_U);
      Serial.print("pwm = [");
      Serial.print(legsAngle[0]);
      for (int i=1;i<12;i++){
        Serial.print(", ");
        Serial.print(legsAngle[i]);
      }
      Serial.println("]");
      
    #endif //DEBUGGER
        
    spidy.checkInsideMinMax(legsAngle); // Check if the angles send are inside the min max.
    spidy.refreshLegs(legsAngle);

    spidy.readLegsPosition(current_legsAngle);
    set_current_angles(current_legsAngle);

    #ifdef DEBUGGER  
    
      Serial.print("Distance_U = ");
      Serial.println(duration_U);
      Serial.print("pwm = [");
      Serial.print(legsAngle[0]);
      for (int i=1;i<12;i++){
        Serial.print(", ");
        Serial.print(legsAngle[i]);
      }
      Serial.println("]");    
    
    Serial.print("pwm = [");
    Serial.print(current_legsAngle[0]);
    for (int i=1;i<12;i++){
      Serial.print(", ");
      Serial.print(current_legsAngle[i]);
    }
    Serial.println("]");    
    
    #endif // DEBUGGER
    
    delay(50);
    
  #endif // COMMANDLINE_CONTROL
}

 #ifdef COMMANDLINE_CONTROL
 
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
   
  #endif
