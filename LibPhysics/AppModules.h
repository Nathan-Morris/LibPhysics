#ifndef _APP_MODULES_
#define _APP_MODULES_

#pragma once

#define _LIB_PHYSICS_DOUBLE_PRECISION
#define _LIB_PHYSICS_USING_NAMESPACES

#include "LibPhysics.h"

#include <iostream>
#include <sstream>

#include <conio.h>

typedef void(*PhysicsApp)(void);

static void projectileMotionApp() {
	//
	// Variable Declaration
	//
	FloatType initialVelocityMagnitude;
	Meters initialHeight;
	FloatType theta;
	Seconds time;
	Seconds timeStep;
	FloatType gravitationalAcceleration;
	Vector<2> velocity;
	
	std::string inputBuffer;
	char* inputParseEnd;



	//
	// Get User Input For Variables
	//
	while (1) {
		std::cout << "Projectile Initial Velocity = ";
		std::getline(std::cin, inputBuffer);

		initialVelocityMagnitude = strtoft(inputBuffer.c_str(), &inputParseEnd);

		if (*inputParseEnd || inputBuffer.empty()) {
			std::cout << "Invalid Input Entered" << std::endl;
		}
		else {
			break;
		}
	}

	std::cout << "Projectile Initial Height (def=0m) = ";
	std::getline(std::cin, inputBuffer);
	initialHeight = strtoft(inputBuffer.c_str(), &inputParseEnd);

	while (1) {
		std::cout << "Projectile Launch Angle = ";
		std::getline(std::cin, inputBuffer);

		theta = strtoft(inputBuffer.c_str(), &inputParseEnd);

		if (*inputParseEnd || inputBuffer.empty()) {
			std::cout << "Invalid Input Entered" << std::endl;
		}
		else {
			theta *= pi / 180.0; // to radians
			break;
		}
	}

	std::cout << "Time Step (def=1s) = ";
	std::getline(std::cin, inputBuffer);
	timeStep = strtoft(inputBuffer.c_str(), &inputParseEnd);
	if (timeStep == 0.0) {
		timeStep = 1.0;
	}

	std::cout << "Gravitational Acceleration (def=9.81m/s) = ";
	std::getline(std::cin, inputBuffer);
	gravitationalAcceleration = strtoft(inputBuffer.c_str(), &inputParseEnd);
	if (gravitationalAcceleration == 0.0) {
		gravitationalAcceleration = 9.81;
	}



	//
	// Variable Definition
	//

	time = 0.0;
	velocity[Dim::X] = initialVelocityMagnitude * cos(theta);
	velocity[Dim::Y] = initialVelocityMagnitude * sin(theta);



	//
	// App
	//

	while (1) {
		if (_getch() == 'q' || _getch() == 'Q') {
			break;
		}

		// go ahead, sue me...
		system("cls");

		velocity[Dim::Y] = (initialVelocityMagnitude * sin(theta)) - (gravitationalAcceleration * time);

		std::cout << "Time = " << time << std::endl;

		std::cout << "Position = ( " << (velocity[Dim::X] * time) << ", ";
		std::cout << (initialVelocityMagnitude * sin(theta) * time) - (.5 * gravitationalAcceleration * (time * time));
		std::cout << " )\n";

		std::cout << "Velocity = " << velocity << "  ||" << velocity.magnitude() << "||\n";

		time += timeStep;

		while (!_kbhit());
	}
}

#endif