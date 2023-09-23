#include "Tools.h"



double RadiansToAngles(double radians) {
	double PI = 3.14159265;
	return radians / PI * 180.0;
}
double AnglesToRadians(double angle) {
	double PI = 3.14159265;
	return angle * PI / 180.0;
}