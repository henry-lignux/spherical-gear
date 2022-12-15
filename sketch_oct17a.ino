#include "spherical-gear.h" // allows program to use our library

void setup() {
  // put your setup code here, to run once:
  int motor1_pin = 7; //vertical 
  int motor2_pin = 8; //horizontal
  int claw_pin = 9;
  int pos = 0;
  SphericalGear sg(motor1_pin,motor2_pin);
  Servo claw_servo;
  claw_servo.attach(claw_pin); // initialize motor
  //we want the arm to reach down, then grab with the claw, then pull back up
  //we might want to go back down and release the claw as well
  
  // open claw
  openclaw(claw_servo, 45);
  // move arm down
  move(0,0,30);
  //close claw 
  closeclaw(claw_servo, 0);
  //move arm up
  move(80,0, 30);
  //move arm down
  move(0,0,30);
  //open claw
  openclaw(claw_servo, 45);
  //move arm up
  move(80,0, 30);
}


}
void loop() {
  // put your main code here, to run repeatedly
  
}
