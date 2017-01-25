/**
 * ultrasound.h
 * 
 * If ultrasound_setup() is called the function update_duration_U will be usable and each 
 * time called save in the duration_U variable the flight time of the ultrasound
 */

#ifndef _ULTRASOUND_H_

  #define _ULTRASOUND_H_  
  
  #define TrigerPin 22 //Trigger pin of HC-SR04   //previously 7
  #define ListenPin 24 //Echo pin of HC-SR04      //previously 8

  void ultrasound_setup()
  {
    pinMode(ListenPin, INPUT);
    pinMode(TrigerPin, OUTPUT);
  }
  
  long microsecondsToCentimeters(long microseconds)
  {
    return microseconds / 29 / 2;
  }
  
  // Get distance from the ultrasound sensor
  void update_duration_U()
  {
    digitalWrite(TrigerPin, LOW);    //securing 0 in trigger pin
    delayMicroseconds(2);            //for 2 us
    digitalWrite(TrigerPin, HIGH);   //fixing 1 in trigger pin
    delayMicroseconds(5);            //for 5 us
    digitalWrite(TrigerPin, LOW);    //fixing 0 back
  
    duration_U = pulseIn(ListenPin, HIGH);    //save valor of time echo takes to come
    //cm_U = microsecondsToCentimeters(duration_U); //changes s to m

    /*Serial.print(cm_U);
    Serial.print("cm");
    Serial.println();  */
  }

#endif // _ULTRASOUND_H_
