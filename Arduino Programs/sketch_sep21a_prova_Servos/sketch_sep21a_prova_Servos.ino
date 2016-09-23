#include<Servo.h>

#define PIN_SERVO 9
#define MYSERIAL Serial
#define BAUDRATE 9600

Servo myServo;

//int val; // This variable reads the value from the analog pin
char syllable[6];
char data;
int j=0;
int intDegrees;
String degrees;
int x=0,i = 0;
bool comFinished= false;
void setup() {
  // put your setup code here, to run once:
  MYSERIAL.begin(BAUDRATE);
  myServo.attach(PIN_SERVO);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(comFinished) {
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
  }
  else{
    degrees = " ";
  }
}

void serialEvent(){
  while(MYSERIAL.available()) {
    data=(char)MYSERIAL.read();    
    if (data != '\n'){
      syllable[i++]=data;   
    } else{
        comFinished = true; 
       x=i;
       i=0;
    }
  }
}
