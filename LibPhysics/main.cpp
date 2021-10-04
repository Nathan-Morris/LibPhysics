#include <iostream>

#include "Units.h"
#include "Vector.h"
#include "Matrix.h"

using namespace std;
using namespace physics_units;
using namespace physics_collections;

//http://www.math.odu.edu/~bogacki/cgi-bin/lat.cgi

int main() {
	Matrix<3, 2> m = {
		{ 3, 3 },
		{ 2, 2 },
		{ 1, 1 }
	};


	cout << m.toREF() << endl;
}