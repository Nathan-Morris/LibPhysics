#define _PHYSICS_DOUBLE_PRECISION

#include <iostream>

#include "Units.h"
#include "Vector.h"
#include "Matrix.h"

using namespace std;
using namespace physics_units;
using namespace physics_collections;

//http://www.math.odu.edu/~bogacki/cgi-bin/lat.cgi

int main() {
	Matrix<2, 7> m = {
		{ -10, .6, 6, 100, 5, .44, -9 },
		{ 7, 5, 6, 12, .112, 30, 0 },
	};


	cout << m.toREF() << endl;
}