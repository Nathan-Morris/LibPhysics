//#include "PhysicsGlobalInclude.h"

#include <iostream>

#include "Units.h"

using namespace std;

int main() {
	Seconds s(1);
	Minutes m(1);

	m += s;

	cout << m << endl;
}