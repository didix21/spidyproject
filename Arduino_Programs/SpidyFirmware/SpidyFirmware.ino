#include "main.h"


void setup() {
  // put your setup code here, to run once:
  MYSERIAL.begin(9600);
  spidy.l1s1.attach(L1S1_PIN);
  delay(500);
  spidy.l1s2.attach(L1S2_PIN);
  delay(500);
  spidy.l2s1.attach(L2S1_PIN);
  delay(500);
  spidy.l2s2.attach(L2S2_PIN);
//  delay(500);
//  spidy.l3s1.attach(L3S1_PIN);
//  delay(500);
//  spidy.l3s2.attach(L3S2_PIN);
//  delay(500);
//  spidy.l4s1.attach(L4S1_PIN);
//  delay(500);
//  spidy.l4s2.attach(L4S2_PIN);
//  delay(500);
//  spidy.l5s1.attach(L5S1_PIN);
//  delay(500);
//  spidy.l5s2.attach(L5S2_PIN);
//  delay(500);
//  spidy.l6s1.attach(L6S1_PIN);
//  delay(500);
//  spidy.l6s2.attach(L6S2_PIN);
//  delay(500);
  //spidy.attachServos();
  //init_comunication();
  //ultrasound_setup();

}

void loop() {
  // put your main code here, to run repeatedly:
   //MYSERIAL.println(" Program has started");
  commandLine();
  //spidy.setSpidyUp();

}

   void serialEvent(){
      int i;
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
