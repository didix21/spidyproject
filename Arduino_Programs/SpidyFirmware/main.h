/**
 * Main.h
 */

#ifndef _MAIN_H_

  #define _MAIN_H_
   
  #include "configuration.h"
  #include "spidy.h"
  //#include <Wire.h>
  #include "comunication.h"
  #include "ultrasound.h"
  #include "messages.h"


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
    int intDegrees;
    String degrees;
    int x=0;
    bool comFinished= false;
    bool manual = true;
    int actualServo;
   
    void commandLine() {
      static String whichServo, command;
      static bool legCommandChoose = false, refreshMode = false;
      int j=0;
      static uint8_t arrayOfDegrees[11]={90,90,90,90,90,90,90,90,90,90,90}, refreshModeCounter = 0;
      if(comFinished) { // if serial has finished of reading then...
        switch(syllable[0]) { // It is looked for the first character
          case 'l': // if the first character is a l it means will control servo legs
          
            whichServo = "";
            for(j=0; j<x; j++) whichServo += syllable[j]; // Read wich servo has been chosen
            legCommandChoose = true;
            comFinished = false;
            
          break;
          
          case 'c': // if the first command is 'c' it means is a 'c+command'
          
             command = "";
             legCommandChoose = false;
             for(j=0; j<x; j++) command += syllable[j]; // read the command

             // Compares which command has been chosen
             if(command == "crest") {
                COMMAND_SENT(command); //Print: <<Command Sent: crest>>
                spidy.setSpidyRest();
             }
             else if (command == "cdown") {
                COMMAND_SENT(command);
                spidy.setSpidyDown();
             }
             else if (command == "cup") {
                COMMAND_SENT(command);
                spidy.setSpidyUp();       
             }
             else if (command == "crefresh") {
                COMMAND_SENT(command);
                refreshMode = true;
             }
             comFinished = false;
             
          break;
        }
 
        if(legCommandChoose) { // If legCommandChoose is true, we can controll each servo via commands
          for(j=0; j<x; j++){
              degrees += syllable[j];
            }
          PRINT_DEGREES(degrees); // Print: << Degrees: nº degrees >>
          intDegrees=degrees.toInt();
          comFinished = false;
         if (whichServo.equals("l1s1")) {
            SERVO_SENT(whichServo); // Print: << Servo Sent: lnºsnº >>
            spidy.l1s1.write(intDegrees);
         }
         else if (whichServo == "l1s2") {
            SERVO_SENT(whichServo);
            spidy.l1s2.write(intDegrees);
         }
         else if (whichServo == "l2s1") {
           SERVO_SENT(whichServo);
           spidy.l2s1.write(intDegrees);
         }
         else if (whichServo == "l2s2") {
           SERVO_SENT(whichServo);
           spidy.l2s2.write(intDegrees);
         }
         else if (whichServo == "l3s1") {
           SERVO_SENT(whichServo);
           spidy.l3s1.write(intDegrees);
         }
         else if (whichServo == "l3s2") {
           SERVO_SENT(whichServo);
           spidy.l3s2.write(intDegrees);
         }
         else if (whichServo == "l4s1") {
           SERVO_SENT(whichServo);
           spidy.l4s1.write(intDegrees);
         }
         else if (whichServo == "l4s2") {
           SERVO_SENT(whichServo);
           spidy.l4s2.write(intDegrees);
         }
         else if (whichServo == "l5s1") {
           SERVO_SENT(whichServo);
           spidy.l5s1.write(intDegrees);
         }
         else if (whichServo == "l5s2") {
           SERVO_SENT(whichServo);
           spidy.l5s2.write(intDegrees);
         }
         else if (whichServo == "l6s1") {
           SERVO_SENT(whichServo);
           spidy.l6s1.write(intDegrees);
         }
         else if (whichServo == "l6s2") {
           SERVO_SENT(whichServo);
           spidy.l6s2.write(intDegrees);
         }
        }
        
        if(refreshMode) { // refreshMode allows to modify all the servors writing the number of degrees eleven times
          if(refreshModeCounter <= 11) {
            for(j=0; j<x; j++){
                degrees += syllable[j];
              }
            MYSERIAL.print("Servo: ");
            MYSERIAL.print(refreshModeCounter);
            MYSERIAL.print(" -> ");
            PRINT_DEGREES(degrees); // Print: << Degrees: nº degrees >>
            intDegrees=degrees.toInt();
            
            arrayOfDegrees[refreshModeCounter] = (uint8_t)intDegrees;
            refreshModeCounter++;
          } 
          else {
            spidy.refreshLegs(arrayOfDegrees); // Once the arrayOfDegrees has been filled, we call refreshLegs method.
            refreshModeCounter = 0;            
          }
        }
      }
      else{
        degrees = " ";
      }
    }
 
 

 #endif // COMMANDLINE_CONTROL
  
#endif // _MAIN_H_
