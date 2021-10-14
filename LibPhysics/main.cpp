#define _LIB_PHYSICS_DOUBLE_PRECISION

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
	FloatType initialHeight,
	FloatType initialVelocity,
	FloatType theta
) {
	FloatType g = 9.81;
	FloatType time = 0;

	theta *= pi / 180.0; // to radians

	Vector<2> velocity = { initialVelocity * cos(theta), initialVelocity * sin(theta) };

	cout << "Init = " << velocity << " -> ||" << velocity.magnitude() << "||\n\n";

	while (1) {
		if (_kbhit()) {
			if (_getch() == 'q') {
				break;
			}

			velocity[Dim::Y] = (initialVelocity * sin(theta)) - ( g * time );

			time += .25;

			cout << "( " << (velocity[Dim::X] * time) << ", " << (((initialVelocity * sin(theta) * time) - (.5 * g * (time * time))) + initialHeight) << ")" << endl;//" -> " << velocity << " -> ||" << velocity.magnitude() << "||" << endl;
		}
	}
}

int main() {
	projectileMotion(20, 10, 30);
}