

/**
 * Defines
 */
#define PIN_SERVO 9
#define MYSERIAL Serial
#define BAUDRATE 9600
// Servo PINS
#define PIN_P1_S1 2 
#define PIN_P1_S2 3
#define PIN_P2_S1 4 
#define PIN_P2_S2 5
#define PIN_P3_S1 6 
#define PIN_P3_S2 7

/**
 * Global Variables
 */
Servo myServo, p1s1, p1s2, p2s1, p2s2, p3s1, p3s2;

//int val; // This variable reads the value from the analog pin
char syllable[12];
char data;
int j=0;
int intDegrees;
String degrees;
int x=0,i = 0;
bool comFinished= false;
bool manual = true;
int actualServo;
