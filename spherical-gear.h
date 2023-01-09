#include <Servo.h> // for the motor
#include <cmath> // for the math
#define TIME_ITERATION 10 // used for servo delay
#define GEAR_RATIO_1 1.143 // this motor rotates the spherical gear vertically
#define GEAR_RATIO_2 1.0 // this motor rotates the spherical gear horizontally
#define MAGIC_NUMBER_RED 0.722 //the coefficient we need to multiply to turn the servo properly
#define MAGIC_NUMBER_BLACK 1.047 // black motor is used for the claw
#define MOTOR_COEFFICIENT_1 GEAR_RATIO_1 * MAGIC_NUMBER_RED
#define MOTOR_COEFFICIENT_2 GEAR_RATIO_2 * MAGIC_NUMBER_RED 
#define CLAW_DELAY 500 //used for claw delay when opening/closing claw

class SphericalGear {
  private:
    Servo servo1; // servo object for motor that changes theta
    Servo servo2; // servo object for motor that changes phi
    double theta; // verticle angle
    double phi; // horizontal angle
	public:
		SphericalGear(int pin1, int pin2) {
      // initializing the motors
      servo1.attach(pin1);
      servo2.attach(pin2);
      // initializing the angles
      //angle of motor
      theta = 0;
      phi = 0;
		}
    void move(double delta_theta, double delta_phi, double angular_speed) {
      // radius is assumed to be 1
      // convert from spherical angle to motor angle
      // measured in degrees; from mr. nims's equation
      //theta is the vertical angle
      //phi is the horizontal angle
       double total_angle_change = acos( sin((theta*MOTOR_COEFFICIENT_1))*sin((theta*MOTOR_COEFFICIENT_1)+delta_theta*MOTOR_COEFFICIENT_1)*cos((phi * MOTOR_COEFFICIENT_2) - delta_phi * MOTOR_COEFFICIENT_2)
       + cos((theta*MOTOR_COEFFICIENT_1))*cos((theta*MOTOR_COEFFICIENT_1)+delta_theta*MOTOR_COEFFICIENT_1) );
      double time = total_angle_change / angular_speed; // in miliseconds
      //changed theta and phi speed to angle_1_speed and angle_2_speed
      double theta_speed = delta_theta*MOTOR_COEFFICIENT_1 / time;
      double phi_speed = delta_phi*MOTOR_COEFFICIENT_2 / time;
      for(int t = 0; t <= time; t+=TIME_ITERATION) { 
	      // iterates over TIME_ITERATION miliseconds 
	      servo1.write(theta); // moves motor to theta
        servo2.write(phi); // moves motor to phi
        //changed theta_speed and phi_speed to angle/ANGLE_CONVERT
        theta += (theta_speed/MOTOR_COEFFICIENT_1)*TIME_ITERATION;
        phi += (phi_speed/MOTOR_COEFFICIENT_2)*TIME_ITERATION;
        delay(TIME_ITERATION);
      }
      theta = servo1.read();
      phi = servo2.read();
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
