#ifdef ARDUINO_MEGA

#include "SpidyMEGA.h"

  /**
   *  Constructor
   */
  SpidyMEGA::SpidyMEGA() {      
       attachServos(); // Init Servos
  }

  void SpidyMEGA::attachServos() {
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

  }

  /**
   * Sent all the servos to rest
   */
  void SpidyMEGA::setSpidyRest() {

    l1s1.write(L1S1_REST);
    l1s2.write(L1S2_REST);
    l2s1.write(L2S1_REST);
    l2s2.write(L2S2_REST);
    l3s1.write(L3S1_REST);
    l3s2.write(L3S2_REST);
    l4s1.write(L4S1_REST);
    l4s2.write(L4S2_REST);
    l5s1.write(L5S1_REST);
    l5s2.write(L5S2_REST);
    l6s1.write(L6S1_REST);
    l6s2.write(L6S2_REST);

   }

   /**
    * To rise Spidy
    */
   void SpidyMEGA::setSpidyUp() {

    l1s2.write(L1S2_MAX);
    l2s2.write(L2S2_MAX);
    l3s2.write(L3S2_MAX);
    l4s2.write(L4S2_MAX);
    l5s2.write(L5S2_MAX);
    l6s2.write(L6S2_MAX);

   }

  /**
   * Set down Spidy
   */
   void SpidyMEGA::setSpidyDown() {

    l1s2.write(L1S2_MIN);
    l2s2.write(L2S2_MIN);
    l3s2.write(L3S2_MIN);
    l4s2.write(L4S2_MIN);
    l5s2.write(L5S2_MIN);
    l6s2.write(L6S2_MIN);

   }

  /**
   * This function is in charge of refresh all the servo legs.
   * Possible some time delays will be implemented in futur to
   * avoid high inductances and Arduino Saturation.
   */
   void SpidyMEGA::refreshLegs(uint8_t *legsAngle) {

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

  /**
   * This function read all the actual servo values
   */
   void SpidyMEGA::readLegsPosition(uint8_t *legsPosition) {

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

   }

#endif // ARDUINO_MEGA
