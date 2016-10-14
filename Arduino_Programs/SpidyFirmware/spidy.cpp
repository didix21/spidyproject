
#include "spidy.h"
  // Constructor
  Spidy::Spidy() {
    l1s1.attach(L1S1_PIN);
    l1s2.attach(L1S2_PIN);
    l2s1.attach(L2S1_PIN);
    l2s2.attach(L2S2_PIN);
    l3s1.attach(L3S1_PIN);
    l3s2.attach(L3S2_PIN);
    l4s1.attach(L4S1_PIN);
    l4s2.attach(L4S2_PIN);
    l5s1.attach(L5S1_PIN);
    l5s2.attach(L5S2_PIN);
    l6s1.attach(L6S1_PIN);
    l6s2.attach(L6S2_PIN);
  }

  // Sent all the servos to rest
  void Spidy::setSpidyRest() {
    l1s1.write(L1S1_MIN);
    l1s2.write(L1S2_REST);
    delay(100); //It is a matter of energy
    l2s1.write(L2S1_MIN);
    l2s2.write(L2S2_REST);
    delay(100);
    l3s1.write(L3S1_MIN);
    l3s2.write(L3S2_REST);
    delay(100);
    l4s1.write(L4S1_MIN);
    l4s2.write(L4S2_REST);
    delay(100);
    l5s1.write(L5S1_MIN);
    l5s2.write(L5S2_REST);
    delay(100);
    l6s1.write(L6S1_MIN);
    l6s2.write(L6S2_REST);
   }

   // To rise Spidy
   void Spidy::setSpidyUp() {
    l1s1.write(L1S1_MAX);
    l2s1.write(L2S1_MAX);
    l3s1.write(L3S1_MAX);
    l4s1.write(L4S1_MAX);
    l5s1.write(L5S1_MAX);
    l6s1.write(L6S1_MAX);
    
   }

  // Set down Spidy
   void Spidy::setSpidyDown() {
    l1s1.write(L1S1_MIN);
    l2s1.write(L2S1_MIN);
    l3s1.write(L3S1_MIN);
    l4s1.write(L4S1_MIN);
    l5s1.write(L5S1_MIN);
    l6s1.write(L6S1_MIN);
   }

   void Spidy::refreshLegs(uint8_t *legsAngle) {
    
   }

