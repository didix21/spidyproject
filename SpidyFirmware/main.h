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
    

    static uint8_t legsAngle[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    static uint8_t current_legsAngle[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

   #ifdef COMMANDLINE_CONTROL
    void commandLine() {

      static String whichServo, command;
      static bool legCommandChoose = false, refreshMode = false;
      static uint8_t arrayOfDegrees[11]={90,90,90,90,90,90,90,90,90,90,90}, refreshModeCounter = 0;

      if(comFinished) { // if serial has finished of reading then...

        if(syllable[0] == 'l') { // if the first character is a l it means will control servo legs
            whichServo = "";
            for(j=0; j<x; j++) whichServo += syllable[j]; // Read wich servo has been chosen
            legCommandChoose = true;
          }
          else if(syllable[0] == 'c') { // if the first command is 'c' it means is a 'c+command'
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
          }
          if(legCommandChoose) {
            if(syllable[0] != 'l') {
              for(j=0; j<x; j++){
                  degrees += syllable[j];
                }
              PRINT_DEGREES(degrees); // Print: << Degrees: nº degrees >>
              intDegrees=degrees.toInt();
           }
           if (whichServo.equals("l1s1")) {
              SERVO_SENT(whichServo); // Print: << Servo Sent: lnºsnº >>
              #if defined(ARDUINO_MEGA)
                spidy.l1s1.write(intDegrees);
              #elif defined(PCA9685_BOARD)
                spidy.spidypca.refreshOneLeg(0, intDegrees);
              #endif
           }
           else if (whichServo == "l1s2") {
              SERVO_SENT(whichServo);
              #if defined(ARDUINO_MEGA)
                spidy.l1s2.write(intDegrees);
              #elif defined(PCA9685_BOARD)
                spidy.spidypca.refreshOneLeg(1, intDegrees);
              #endif
           }
           else if (whichServo == "l2s1") {
             SERVO_SENT(whichServo);
             #if defined(ARDUINO_MEGA)
               spidy.l2s1.write(intDegrees);
             #elif defined(PCA9685_BOARD)
               spidy.spidypca.refreshOneLeg(2, intDegrees);
             #endif
           }
           else if (whichServo == "l2s2") {
             SERVO_SENT(whichServo);
            #if defined(ARDUINO_MEGA)
              spidy.l2s2.write(intDegrees);
            #elif defined(PCA9685_BOARD)
              spidy.spidypca.refreshOneLeg(3, intDegrees);
            #endif
           }
           else if (whichServo == "l3s1") {
             SERVO_SENT(whichServo);
            #if defined(ARDUINO_MEGA)
              spidy.l3s1.write(intDegrees);
            #elif defined(PCA9685_BOARD)
              spidy.spidypca.refreshOneLeg(4, intDegrees);
            #endif
           }
           else if (whichServo == "l3s2") {
             SERVO_SENT(whichServo);
            #if defined(ARDUINO_MEGA)
              spidy.l3s2.write(intDegrees);
            #elif defined(PCA9685_BOARD)
              spidy.spidypca.refreshOneLeg(5, intDegrees);
            #endif
           }
           else if (whichServo == "l4s1") {
             SERVO_SENT(whichServo);
            #if defined(ARDUINO_MEGA)
              spidy.l4s1.write(intDegrees);
            #elif defined(PCA9685_BOARD)
              spidy.spidypca.refreshOneLeg(6, intDegrees);
            #endif
           }
           else if (whichServo == "l4s2") {
             SERVO_SENT(whichServo);
            #if defined(ARDUINO_MEGA)
              spidy.l1s1.write(intDegrees);
            #elif defined(PCA9685_BOARD)
              spidy.spidypca.refreshOneLeg(7, intDegrees);
            #endif
           }
           else if (whichServo == "l5s1") {
             SERVO_SENT(whichServo);
            #if defined(ARDUINO_MEGA)
              spidy.l5s1.write(intDegrees);
            #elif defined(PCA9685_BOARD)
              spidy.spidypca.refreshOneLeg(8, intDegrees);
            #endif
           }
           else if (whichServo == "l5s2") {
             SERVO_SENT(whichServo);
            #if defined(ARDUINO_MEGA)
              spidy.l5s2.write(intDegrees);
            #elif defined(PCA9685_BOARD)
              spidy.spidypca.refreshOneLeg(9, intDegrees);
            #endif
           }
           else if (whichServo == "l6s1") {
             SERVO_SENT(whichServo);
            #if defined(ARDUINO_MEGA)
              spidy.l6s1.write(intDegrees);
            #elif defined(PCA9685_BOARD)
              spidy.spidypca.refreshOneLeg(10, intDegrees);
            #endif
           }
           else if (whichServo == "l6s2") {
             SERVO_SENT(whichServo);
            #if defined(ARDUINO_MEGA)
              spidy.l1s1.write(intDegrees);
            #elif defined(PCA9685_BOARD)
              spidy.spidypca.refreshOneLeg(11, intDegrees);
            #endif
           }
        }
        else if (refreshMode) {
           if(refreshModeCounter <= 11 && syllable[0] != 'c') {
            for(j=0; j<x; j++){
                degrees += syllable[j];
              }
            intDegrees=degrees.toInt();
            arrayOfDegrees[refreshModeCounter] = (uint8_t)intDegrees;
            MYSERIAL.print("Servo: ");
            MYSERIAL.print(refreshModeCounter);
            MYSERIAL.print(" -> ");
            PRINT_DEGREES((uint8_t)intDegrees); // Print: << Degrees: nº degrees >>

            refreshModeCounter++;
          }
          else if(syllable[0] != 'c'){
            /***************************************************************************
             *  All this prints arrayOfDegrees = {nº,nº,nº,nº,nº,nº,nº,nº,nº,nº,nº,nº} *
             ***************************************************************************/
            MYSERIAL.println(ASTERISKS);
            MYSERIAL.print("\t arrayOfDegrees = {"); // Prints "arrayOfDegrees = { "
            for(j = 0; j <= 11; j++) {
              MYSERIAL.print(arrayOfDegrees[j]);
              if(j < 11) MYSERIAL.print(",");
            }
            MYSERIAL.println("}");
            MYSERIAL.println(ASTERISKS);
           /***************************************************************************
            ***************************************************************************
            ***************************************************************************/
            //spidy.refreshLegs(arrayOfDegrees); // Once the arrayOfDegrees has been filled, we call refreshLegs method.
            refreshModeCounter = 0;
          }
        }
        comFinished = false;
      }
      else{
        degrees = " ";
      }
    }

  #endif // COMMANDLINE_CONTROL

#endif // _MAIN_H_
