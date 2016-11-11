#include "main.h"



void setup() {
  // put your setup code here, to run once:
  MYSERIAL.begin(BAUDRATE);
  MYSERIAL.println(" Program has started");
  //spidy.setSpidyRest();

}

void loop() {
  // put your main code here, to run repeatedly:

  commandLine();
  //spidy.setSpidyUp();

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
