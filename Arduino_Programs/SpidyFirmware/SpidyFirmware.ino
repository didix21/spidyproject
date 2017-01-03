#include "main.h"


void setup() {
  // put your setup code here, to run once:
  MYSERIAL.begin(BAUDRATE);
  if(MYSERIAL.available()){
    MYSERIAL.println(ASTERISKS);
    MYSERIAL.println(SPIDY_FIRMWARE);
    MYSERIAL.println(ASTERISKS);
  }
//  spidy.l1s1.attach(L1S1_PIN);
//  spidy.l1s2.attach(L1S2_PIN);
//  spidy.l2s1.attach(L2S1_PIN);
//  spidy.l2s2.attach(L2S2_PIN);
//  spidy.l3s1.attach(L3S1_PIN);
//  spidy.l3s2.attach(L3S2_PIN);
//  spidy.l4s1.attach(L4S1_PIN);
//  spidy.l4s2.attach(L4S2_PIN);
//  spidy.l5s1.attach(L5S1_PIN);
//  spidy.l5s2.attach(L5S2_PIN);
//  spidy.l6s1.attach(L6S1_PIN);
//  spidy.l6s2.attach(L6S2_PIN);
  spidy.attachServos();
  
  //init_comunication();
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
