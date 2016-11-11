/**
 * Main.h
 */

#ifndef _MAIN_H_

  #define _MAIN_H_
   
  #include "configuration.h"
  #include "spidy.h"
  #include <Wire.h>



  #ifdef COMMANDLINE_CONTROL

    /*
     * COMMAND LINE: 
     * The command line allows to the user to control the spidy robot using commands,
     * there are two types of command 'c+commands' and lnºpnº. The first one are used
     * to execute especific accions. The other one it is used to change the position 
     * of each servo of each leg where nº is a number.
     * 
     * ################## 'c+coommands' availables ##################
     * To use it 'c+command' only it is nedded to write the command.
     * 
     * 
     * "crest": put spidy in rest position.
     * "cdown": put spidy in down position.
     * "cup": put spidy in up position.
     * 
     * ########################### lnºpnº ###########################
     * 
     * To use 'lnºpnº' command is needed to write first the command
     * and click intro and then write the degrees. For example type
     * l1s1, click intro and then write the number of degrees, for 
     * example 60 and click intro.
     * 
     * "l1s1": leg 1 servo 1
     * "l1s2": leg 1 servo 2
     * "l2s1": leg 2 servo 1
     * "l2s2"
     * "l3s1"
     * "l3s2"
     * "l4s1"
     * "l4s2"
     * "l5s1"
     * "l5s2"
     * "l6s1"
     * "l6s2"
     */
  
    //int val; // This variable reads the value from the analog pin
    Spidy spidy;
    char syllable[12];
    char data;
    int j=0;
    int intDegrees;
    String degrees;
    int x=0,i = 0;
    bool comFinished= false;
    bool manual = true;
    int actualServo;
  
    void commandLine() {
      String whichServo, command;
      bool legCommandChoose = false;

      if(comFinished) { // if serial has finished of reading then...
        if(syllable[0] == 'l') { // if the first character is a l it means will control servo legs
            whichServo = "";
            for(j=0; j<x; j++) whichServo += syllable[j]; // Read wich servo has been chosen
            legCommandChoose = true;
            comFinished = false;
          }
          else if(syllable[0] == 'c') { // if the first command is 'c' it means is a 'c+command'
             command = "";
             legCommandChoose = false;
             for(j=0; j<x; j++) command += syllable[j]; // read the command

             // Compares which command has been chosen
             if(command == "crest") {
                MYSERIAL.println (" Command Send: crest");
                spidy.setSpidyRest();
             }
             else if (command == "cdown") {
                MYSERIAL.println (" Command Send: cdown");
                spidy.setSpidyDown();
             }
             else if (command == "cup") {
                MYSERIAL.println (" Command Send: cup");
                spidy.setSpidyUp();       
             }
             comFinished = false;
          }
          
          if(legCommandChoose) {
            for(j=0; j<x; j++){
                degrees += syllable[j];
              }
            MYSERIAL.print("Send: ");
            MYSERIAL.print(degrees);
            MYSERIAL.println();
            //MYSERIAL.println(" º");
            intDegrees=degrees.toInt();
            comFinished = false;
           if (whichServo.equals("l1s1")) {
              MYSERIAL.println (" Servo Sent: L1S1");
              spidy.l1s1.write(intDegrees);
           }
           else if (whichServo == "l1s2") {
              MYSERIAL.println (" Servo Sent: L1S2");
              spidy.l1s2.write(intDegrees);
           }
           else if (whichServo == "l2s1") {
             MYSERIAL.println (" Servo Sent: L2S1");
             spidy.l2s1.write(intDegrees);
           }
           else if (whichServo == "l2s2") {
             MYSERIAL.println (" Servo Sent: L2S2");
             spidy.l2s2.write(intDegrees);
           }
           else if (whichServo == "l3s1") {
             MYSERIAL.println (" Servo Sent: L3S1");
             spidy.l3s1.write(intDegrees);
           }
           else if (whichServo == "l3s2") {
             MYSERIAL.println (" Servo Sent: L3S2");
             spidy.l3s2.write(intDegrees);
           }
           else if (whichServo == "l4s1") {
             MYSERIAL.println (" Servo Sent: L4S1");
             spidy.l4s1.write(intDegrees);
           }
           else if (whichServo == "l4s2") {
             MYSERIAL.println (" Servo Sent: L4S2");
             spidy.l4s2.write(intDegrees);
           }
           else if (whichServo == "l5s1") {
             MYSERIAL.println (" Servo Sent: L5S1");
             spidy.l5s1.write(intDegrees);
           }
           else if (whichServo == "l5s2") {
             MYSERIAL.println (" Servo Sent: L5S2");
             spidy.l5s2.write(intDegrees);
           }
           else if (whichServo == "l6s1") {
             MYSERIAL.println (" Servo Sent: L6S1");
             spidy.l6s1.write(intDegrees);
           }
           else if (whichServo == "l6s2") {
             MYSERIAL.println (" Servo Sent: L6S2");
             spidy.l6s2.write(intDegrees);
           }
      }      
      else{
        degrees = " ";
      }
     }
    }
  
 

 #endif // COMMANDLINE_CONTROL
  
#endif // _MAIN_H_
