
#ifndef _MESSAGES_H_

   #define _MESSAGES_H_

   #define SERVO_SENT(X) do{MYSERIAL.print("Servo Sent: "); MYSERIAL.println(X);} while(0)
   #define PRINT_DEGREES(X) do{MYSERIAL.print("Degrees: "); MYSERIAL.println(X);} while(0)
   #define COMMAND_SENT(X) do{MYSERIAL.print("Command Sent: "); MYSERIAL.println(X);} while(0)

   #define ASTERISKS "***************************************************************************"
   #define SPIDY_FIRMWARE "**************************This is Spidy Firmware***************************" 
#endif
