#define _PHYSICS_DOUBLE_PRECISION

#include <iostream>	

#include "Units.h"
#include "Vector.h"
#include "Matrix.h"
#include "Angles.h"

using namespace std;
using namespace physics_units;
using namespace physics_collections;
using namespace physics_constants;

int main() {
	FloatType theta = 35 * pi / 180;

	Vector<2> a = { 50, 0 };
	Vector<2> b = { 40 * cos(theta), 40 * sin(theta) };
	Vector<2> c = { 0, 30 };

	Vector<2> R = a + b + c;

	cout << R << " ||" << R.magnitude() << "||\n";
}