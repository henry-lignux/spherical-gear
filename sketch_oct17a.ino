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
  int angle_open_claw = 30;
  int angle_close_claw = 10;
  //we want the arm to reach down, then grab with the claw, then pull back up
  //we might want to go back down and release the claw as well
  

  // + angle is downwards, - angle is upwards
  // arm starts at vertical 90 degrees, with claw closed
  
  // open claw
  openclaw(claw_servo, angle_open_claw);
  delay(500);
  // move arm down
  move(90,0,30);
  //close claw 
  closeclaw(claw_servo, angle_close_claw);
  //move arm up
  move(-90,0, 30);
  //move arm down
  delay(500);
  move(90,0,30);
  //open claw
  delay(500);
  openclaw(claw_servo, angle_open_claw);
  delay(500);
  //move arm up
  move(-90,0, 30);
}


}
void loop() {
  // put your main code here, to run repeatedly
  
}
