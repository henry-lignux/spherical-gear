#include <Servo.h> // for the motor
#include <cmath> // for the math
#define TIME_ITERATION 10 // used for servo delay
#define GEAR_RATIO_1 1.0
#define GEAR_RATIO_2 1.0
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
      double total_angle_change = acos( sin((angle1*GEAR_RATIO_1))*sin((angle1*GEAR_RATIO_1)+delta_theta)*cos((angle2*GEAR_RATIO_2)-delta_phi)
       + cos((angle1*GEAR_RATIO_1))*cos((angle1*GEAR_RATIO_1)+delta_theta) );
      double time = total_angle_change / angular_speed; // in miliseconds
      //changed theta and phi speed to angle_1_speed and angle_2_speed
      double angle_1_speed = delta_theta / time;
      double angle_2_speed = delta_phi / time;
      for(int t = 0; t <= time; t+=TIME_ITERATION) { 
	      // iterates over TIME_ITERATION miliseconds 
	      servo1.write(angle1); // moves motor to theta
        servo2.write(angle2); // moves motor to phi
        //changed theta_speed and phi_speed to angle/ANGLE_CONVERT
        angle1 += (angle_1_speed/GEAR_RATIO_1)*TIME_ITERATION;
        angle2 += (angle_2_speed/GEAR_RATIO_2)*TIME_ITERATION;
        delay(TIME_ITERATION);
      }
    }
};
void openclaw (Servo clawmotor, int open_angle) { 
  //takes parameter servo and angle to which the claw should open
  //turn the motor 45 degrees
  clawmotor.write(open_angle);
  delay(CLAW_DELAY);
}
void closeclaw (Servo clawmotor, int close_angle) {
  //close the motor
  clawmotor.write(close_angle);
  delay(CLAW_DELAY);
}