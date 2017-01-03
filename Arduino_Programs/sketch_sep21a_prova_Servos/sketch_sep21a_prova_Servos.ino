#include<Servo.h>
#include "var.h"

String strin2 = "p1s1";
String whichServo, command;

void setup() {
  // put your setup code here, to run once:
  MYSERIAL.begin(BAUDRATE);
  myServo.attach(PIN_SERVO);
  p1s1.attach(PIN_P1_S1);
  p1s2.attach(PIN_P1_S2);
  p2s1.attach(PIN_P2_S1);
  p2s2.attach(PIN_P2_S2);
  p3s1.attach(PIN_P3_S1);
  p3s2.attach(PIN_P3_S2);
  MYSERIAL.println(" All servo attached");

}

void loop() {
  // put your main code here, to run repeatedly:
  exit:
  if(comFinished) {
    if(syllable[0] == 'm') {
      manual = true;
    }
    else if(syllable[0] == 'a') {
      manual = false;
    }
    else if(syllable[0] == 'p') {
      whichServo = "";
      MYSERIAL.println("OK");
      for(j=0; j<x; j++) {
        whichServo += syllable[j];
      }
      comFinished = false;
      goto exit;
    }
    else if(syllable[0] == 'c') {
       command = "";
       for(j=0; j<x; j++) command += syllable[j];
    
       if(command == "crest") {
          MYSERIAL.println (" Command Send: crest");
          delay(500);
          p1s1.write(60);
          p1s2.write(120);
          delay(100);
          p2s1.write(0);
          p2s2.write(60);
          delay(100);
          p3s1.write(70);
          p3s2.write(0);
          delay(100);
          delay(500);
       }
       else if (command == "cdown") {
          MYSERIAL.println (" Command Send: cdown");
          delay(500);
          p1s1.write(60);
          p2s1.write(0);
          p3s1.write(70);
       }
       else if (command == "cup") {
          MYSERIAL.println (" Command Send: cup");
          p1s1.write(180);
          p2s1.write(90);
          p3s1.write(165);        
       }
       else if (command == "cupdown") {
          MYSERIAL.println (" Command Send: cupdown");
          for(j=0; j<10; j++) {
            p1s1.write(180);
            p2s1.write(90);
            p3s1.write(165);     
            delay(750);
            p1s1.write(60);
            p2s1.write(0);
            p3s1.write(70);
            delay(750);            
          }
       }
       comFinished = false;
       goto exit;
    }
      for(j=0; j<x; j++){
          degrees += syllable[j];
        }
        MYSERIAL.print("Send: ");
        MYSERIAL.print(degrees);
        MYSERIAL.println();
        //MYSERIAL.println(" º");
        intDegrees=degrees.toInt();
        myServo.write(intDegrees);
        comFinished = false;
       if (whichServo.equals("p1s1")) {
          MYSERIAL.println (" Servo Sent: P1S1");
          p1s1.write(intDegrees);
       }
       else if (whichServo == "p1s2") {
           MYSERIAL.println (" Servo Sent: P1S2");
          p1s2.write(intDegrees);
       }
       else if (whichServo == "p2s1") {
         MYSERIAL.println (" Servo Sent: P2S1");
         p2s1.write(intDegrees);
       }
       else if (whichServo == "p2s2") {
         MYSERIAL.println (" Servo Sent: P2S2");
         p2s2.write(intDegrees);
       }
       else if (whichServo == "p3s1") {
         MYSERIAL.println (" Servo Sent: P3S1");
         p3s1.write(intDegrees);
       }
       else if (whichServo == "p3s2") {
         MYSERIAL.println (" Servo Sent: P3S2");
         p3s2.write(intDegrees);
       }
  }
  else{
    degrees = " ";
  }
  if(!manual) {
      myServo.write(40);
      delay(500);
      myServo.write(150);
      delay(500);
  }
  
  
}

void serialEvent(){
  while(MYSERIAL.available()) {
    data=(char)MYSERIAL.read();    
    if (data != '\n'){
      syllable[i++]=data;   
    } else{
        MYSERIAL.println("Read finished");
        comFinished = true; 
       x=i;
       i=0;
    }
  }
}
