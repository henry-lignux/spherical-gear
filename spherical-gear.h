#include <Servo.h> // for the motor
#include <cmath> // for the math
#define TIME_ITERATION 10 // used for servo delay
#define GEAR_RATIO_1 1.143 // this gear is attached to the second gear
#define GEAR_RATIO_2 1.0 // this motor attaches directly to the spherical gear
#define MAGIC_NUMBER_RED 0.722 //the coefficient we need to multiply to turn the servo properly
#define MAGIC_NUMBER_BLACK 1.047 
#define CLAW_DELAY 500 //used for claw delay when opening/closing claw

class SphericalGear {
  private:
    Servo servo1; // servo object for motor that changes theta
    Servo servo2; // servo object for motor that changes phi
    double angle1;
    double angle2;
	public:
		SphericalGear(int pin1, int pin2) {
      // initializing the motors
      servo1.attach(pin1);
      servo2.attach(pin2);
      // initializing the angles
      //angle of motor
      angle1 = 0;
      angle2 = 0;
		}
    void move(double delta_theta, double delta_phi, double angular_speed) {
      // radius is assumed to be 1
      // convert from spherical angle to motor angle
      // measured in degrees; from mr. nims's equation
      //theta is the vertical angle
      //phi is the horizontal angle
       double total_angle_change = acos( sin((angle1*GEAR_RATIO_1))*sin((angle1*GEAR_RATIO_1)+delta_theta*MAGIC_NUMBER_RED)*cos((angle2*GEAR_RATIO_2)-delta_phi*MAGIC_NUMBER_RED)
       + cos((angle1*GEAR_RATIO_1))*cos((angle1*GEAR_RATIO_1)+delta_theta*MAGIC_NUMBER_RED) );
      double time = total_angle_change / angular_speed; // in miliseconds
      //changed theta and phi speed to angle_1_speed and angle_2_speed
      double angle_1_speed = delta_theta*MAGIC_NUMBER_RED / time;
      double angle_2_speed = delta_phi*MAGIC_NUMBER_RED / time;
      for(int t = 0; t <= time; t+=TIME_ITERATION) { 
	      // iterates over TIME_ITERATION miliseconds 
	      servo1.write(angle1); // moves motor to theta
        servo2.write(angle2); // moves motor to phi
        //changed theta_speed and phi_speed to angle/ANGLE_CONVERT
        angle1 += (angle_1_speed/GEAR_RATIO_1)*TIME_ITERATION;
        angle2 += (angle_2_speed/GEAR_RATIO_2)*TIME_ITERATION;
        delay(TIME_ITERATION);
      }
      angle1 = servo1.read();
      angle2 = servo2.read();
    }
};
void openclaw (Servo clawmotor, int open_angle) { 
  //takes parameter servo and angle to which the claw should open
  //turn the motor 45 degrees
  clawmotor.write(open_angle*MAGIC_NUMBER_BLACK);
  delay(CLAW_DELAY);
}
void closeclaw (Servo clawmotor, int close_angle) {
  //close the motor
  clawmotor.write(close_angle*MAGIC_NUMBER_BLACK);
  delay(CLAW_DELAY);
}
