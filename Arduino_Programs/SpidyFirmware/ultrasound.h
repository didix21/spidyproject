/**
 * ultrasound.h
 */

#ifndef _ULTRASOUND_H_

  #define _ULTRASOUND_H_  
  
  #define TrigerPin 7  //Trigger pin of HC-SR04
  #define ListenPin 8  //Echo pin of HC-SR04


  void ultrasound_setup()
  {
    pinMode(ListenPin, INPUT);
    pinMode(TrigerPin, OUTPUT);
  }
  
  // Get distance from the ultrasound sensor
  long get_distance_U()
  {
    digitalWrite(TrigerPin, LOW);    //securing 0 in trigger pin
    delayMicroseconds(2);            //for 2 us
    digitalWrite(TrigerPin, HIGH);   //fixing 1 in trigger pin
    delayMicroseconds(5);            //for 5 us
    digitalWrite(TrigerPin, LOW);    //fixing 0 back
  
    duration_U = pulseIn(ListenPin, HIGH);    //save valor of time echo takes to come
    cm_U = microsecondsToCentimeters(duration_U); //changes s to m
  
    /*Serial.print(cm_U);
    Serial.print("cm");
    Serial.println();  */
  }
  
  long microsecondsToCentimeters(long microseconds)
  {
    return microseconds / 29 / 2;
  }

#endif // _ULTRASOUND_H_
