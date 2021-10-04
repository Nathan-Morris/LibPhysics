#include <iostream>

#include "Units.h"
#include "Vector.h"

using namespace std;
using namespace physics_units;
using namespace physics_collections;

int main() {
	Vector<3> v1 = { 1, 2, 3 };
	Vector<3> v2 = { 5, 6, 7 };

	cout << (v1 + v2).normalize().magnitude() << endl;

}