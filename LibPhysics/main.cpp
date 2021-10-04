#include <iostream>

#include "Units.h"

using namespace std;
using namespace physics_units;
using namespace physics_constants;

int main() {
	Minutes m(10);

	m = Seconds(100);

	cout << m << endl;
}