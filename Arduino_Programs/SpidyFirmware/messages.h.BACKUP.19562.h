
#ifndef _MESSAGES_H_

   #define _MESSAGES_H_

   #define SERVO_SENT(X) do{MYSERIAL.print("Servo Sent: "); MYSERIAL.println(X);} while(0)
   #define PRINT_DEGREES(X) do{MYSERIAL.print("Degrees: "); MYSERIAL.println(X);} while(0)
<<<<<<< HEAD
   #define COMMAND_SENT(X) do{MYSERIAL.print("Command Sent: "); MYSERIAL.println(X);} while(0)

   #define ASTERISKS "***************************************************************************"
=======
   #define COMMAND_SENT(X) do{MYSERIAL.print("Command Sent: "); MYSERIAL.println(X);}while(0)
 
>>>>>>> 047d3bb94cbda700f883dcf7855ad830813b04f5

#endif
