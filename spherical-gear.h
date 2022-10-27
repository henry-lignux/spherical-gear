#include <Servo.h> // for the motor
#include <cmath> // for the math

class SphericalGear {
  private:
    Servo servo1; // servo that changes angle1
    Servo servo2; // servo that changes angle2
    double angle1; // theta
    double angle2; // phi
	public:
		SphericalGear(int pin1, int pin2) {
      servo1.attach(pin1);
      servo2.attach(pin2);
      angle1 = 0;
      angle2 = 0;
		}
    void move(double theta, double phi, double angular_speed) {
      double total_angle = acos(cos(theta) * cos(phi)); // in degrees
      double time = total_angle / angular_speed; // in miliseconds
      double theta_speed = theta / time;
      double phi_speed = phi / time;
      for(int t = 0; t <= time; i+=10) {
        // iterates over 10 miliseconds
        servo1.write(angle1);
        servo2.write(angle2);
        angle1 += theta_speed*10;
        angle2 += phi_speed*10;
        delay(10);
      }
    }
};
