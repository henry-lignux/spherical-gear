#include <Servo.h> // for the motor
#include <cmath> // for the math
#define TIME_ITERATION 10 // used for servo delay
class SphericalGear {
  private:
    Servo servo1; // servo object for motor that changes theta
    Servo servo2; // servo object for motor that changes phi
    double theta;
    double phi;
	public:
		SphericalGear(int pin1, int pin2) {
      servo1.attach(pin1);
      servo2.attach(pin2);
      angle1 = 0;
      angle2 = 0;
		}
    void move(double delta_theta, double delta_phi, double angular_speed) {
      // radius is assumed to be 1
      double total_angle_change = acos( sin(theta)*sin(theta+delta_theta)*cos(phi-delta_phi) + cos(theta)*cos(theta+delta_theta) ); // measured in degrees; from mr. nims's equation
      double time = total_angle_change / angular_speed; // in miliseconds
      double theta_speed = delta_theta / time;
      double phi_speed = delta_phi / time;
      for(int t = 0; t <= time; t+=TIME_ITERATION) { 
	      // iterates over TIME_ITERATION miliseconds 
	      servo1.write(theta);
        servo2.write(phi);
        theta += theta_speed*TIME_ITERATION;
        phi += phi_speed*TIME_ITERATION;
        delay(TIME_ITERATION);
      }
    }
};
