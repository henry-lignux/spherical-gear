#include "spherical-gear.h" // allows program to use our library

void setup() {
  // put your setup code here, to run once:
  int motor1_pin = 7;
  int motor2_pin = 8;
  int claw_pin = 9;
  SphericalGear sg(motor1_pin,motor2_pin);
}

void loop() {
  // put your main code here, to run repeatedly:

}
