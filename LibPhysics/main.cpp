#define _PHYSICS_DOUBLE_PRECISION

#include <iostream>	

#include "Units.h"
#include "Vector.h"
#include "Matrix.h"
#include "Angles.h"

#include <conio.h>

using namespace std;
using namespace physics_units;
using namespace physics_collections;
using namespace physics_constants;

static void projectileMotion(
	FloatType initialVelocity,
	FloatType theta
) {
	FloatType a = -9.81;
	FloatType time;

	theta *= pi / 180.0; // to radians

	Vector<2> velocity = { initialVelocity * cos(theta), initialVelocity * sin(theta) };

	while (1) {
		if (_kbhit()) {
			if (_getch() == 'q') {
				break;
			}

			velocity[1]
		}
	}
}

int main() {
	
}