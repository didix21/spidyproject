#include "spidy.h"
  // Constructor
  Spidy::Spidy() {
    
    // Initialize Servo Motors
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

    /*/ Initialize comunication
    init_comunication();
    // Initialize sensors
    ultrasound_setup();*/

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

    // Actualize legs position
    l1s1.write(legsAngle[0]);
    l1s2.write(legsAngle[1]);
    l2s1.write(legsAngle[2]);
    l2s2.write(legsAngle[3]);
    l3s1.write(legsAngle[4]);
    l3s2.write(legsAngle[5]);
    l4s1.write(legsAngle[6]);
    l4s2.write(legsAngle[7]);
    l5s1.write(legsAngle[8]);
    l5s2.write(legsAngle[9]);
    l6s1.write(legsAngle[10]);
    l6s2.write(legsAngle[11]);
    
   }

   uint8_t* Spidy::readLegsPosition(uint8_t *legsAngle) {
    
    uint8_t legsPosition[12]; // Twelve Servo Motors
    // Read actual legs position
    legsPosition[0] = l1s1.read();
    legsPosition[1] = l1s2.read();
    legsPosition[2] = l2s1.read();
    legsPosition[3] = l2s2.read();
    legsPosition[4] = l3s1.read();
    legsPosition[5] = l3s2.read();
    legsPosition[6] = l4s1.read();
    legsPosition[7] = l4s2.read();
    legsPosition[8] = l5s1.read();
    legsPosition[9] = l5s2.read();
    legsPosition[10] = l6s1.read();
    legsPosition[11] = l6s2.read();

    return legsPosition;
   }

   bool checkPosition(uint8_t *legsAngle, uint8_t *legsPosition) {
    
    bool achievedPosition[12]; // This array will be used to know if all the servos has achieved the position
    
    // Check if servos has achieved the position desired
    for(int i = 0; i < 11; i++) {
      // (legsAngle[i] - 10) <= legsPosition[i] <= (legsAngle[i] + 10)
      if((legsPosition[i] >= (legsAngle[i] - 10)) && (legsPosition[i] <= (legsAngle[i] + 10))) { 
        achievedPosition[i] = true;
      } 
      else {
        achievedPosition[i] = false;
      }
    }

    return achievedPosition;
   }
   
