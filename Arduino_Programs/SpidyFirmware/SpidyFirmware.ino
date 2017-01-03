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
  //ultrasound_setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  commandLine();

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
