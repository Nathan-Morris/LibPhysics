#define _PHYSICS_DOUBLE_PRECISION

#include <iostream>

#include "Units.h"
#include "Vector.h"
#include "Matrix.h"

using namespace std;
using namespace physics_units;
using namespace physics_collections;

//http://www.math.odu.edu/~bogacki/cgi-bin/lat.cgi

//https://en.wikipedia.org/wiki/Row_echelon_form#Reduced_row_echelon_form

int main() {
	Matrix<2, 7> m = {
		{ -10, .6, 6, 100, 5, .44, -9 },
		{ 7, 5, 6, 12, .112, 30, 0 },
	};

	Matrix<2, 7> m1 = {
		{ -10, .6, 6, 100, 5, .44, -9 },
		{ 7, 5, 6, 12, .112, 30, 0 },
	};


	cout << m.toREF() << endl << endl;
	cout << m1._toREF() << endl;
}