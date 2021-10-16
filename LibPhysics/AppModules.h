#ifndef _APP_MODULES_
#define _APP_MODULES_

#pragma once

#define _LIB_PHYSICS_DOUBLE_PRECISION
#define _LIB_PHYSICS_USING_NAMESPACES

#include "LibPhysics.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <sstream>

#include <conio.h>

#pragma comment(lib, "glew32")
#pragma comment(lib, "glfw3dll")

typedef void(*PhysicsApp)(void);

static bool graphicsInit() {
	if (!glfwInit()) {
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		return;
	}
}


/*
Compiles and links GLSL vertex / fragment shaders from source
Uses shaders in global program, returns OpenGL program id
*/
static GLuint graphicsProgramShaderCompilationAndLinking(const char* vertexShaderSrc, const char* fragmentShaderSrc) {
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	GLint shaderCompilationResult = GL_FALSE, shaderLogLength = 0;

	glShaderSource(vertexShaderId, 1, &VERTEX_SHADER_SRC, NULL);
	glCompileShader(vertexShaderId);
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &shaderCompilationResult);
	glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &shaderLogLength);

	if (shaderLogLength) {
		char* shaderLogOutputBuffer = new char[shaderLogLength + 1]();
		glGetShaderInfoLog(vertexShaderId, shaderLogLength, NULL, shaderLogOutputBuffer);
		puts(shaderLogOutputBuffer);
		delete[] shaderLogOutputBuffer;
		return 0;
	}

	glShaderSource(fragmentShaderId, 1, &FRAGMENT_SHADER_SRC, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &shaderCompilationResult);
	glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &shaderLogLength);

	if (shaderLogLength) {
		char* shaderLogOutputBuffer = new char[shaderLogLength + 1]();
		glGetShaderInfoLog(fragmentShaderId, shaderLogLength, NULL, shaderLogOutputBuffer);
		puts(shaderLogOutputBuffer);
		delete[] shaderLogOutputBuffer;
		return 0;
	}

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &shaderCompilationResult);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &shaderLogLength);

	if (shaderLogLength) {
		char* shaderLogOutputBuffer = new char[shaderLogLength + 1]();
		glGetProgramInfoLog(programId, shaderLogLength, NULL, shaderLogOutputBuffer);
		puts(shaderLogOutputBuffer);
		delete[] shaderLogOutputBuffer;
		return 0;
	}

	glUseProgram(programId);

	glDetachShader(programId, vertexShaderId);
	glDetachShader(programId, fragmentShaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;
}

static void projectileMotionApp(GLFWwindow* window) {
	//
	// Shader Source Code / Compilation / Linking
	//
	const char* fragmentShaderSource = R"(#version 330 core
		uniform vec3 inColor;
		out vec3 outColor;
		void main() {
			outColor = inColor;
		}
	)";

	const char* vertexShaderSource = R"(#version 330 core
		layout(location = 0) in vec3 vertexPosition_modelspace;
		void main() {
			gl_Position.xyz = vertexPosition_modelspace;
			gl_Position.w = 1.0;
		}
	)";

	GLuint programId = graphicsProgramShaderCompilationAndLinking(vertexShaderSource, fragmentShaderSource);

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
	// Graphics Setup
	//

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 0 -> vector all comp
	// 1 -> vector horizontal comp
	// 2 -> vector vertical comp
	GLfloat vectorVertexPairs[3][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	};

	GLfloat vectorRgbColors[3][3] = {
		{ 1, 1, 1 }, // white
		{ 1, 0, 0 }, // red
		{ 0, 0, 1 }	 // blue	
	};

	GLuint vectorVBOs[3];
	glGenBuffers(3, vectorVBOs);

	GLfloat scale = 100.f;

	GLuint uniformColorVariable = glGetUniformLocation(programId, "inColor");

	//
	// App
	//

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (size_t i = 0; i != 3; i++) {
			glBindBuffer(GL_ARRAY_BUFFER, vectorVBOs[i]);
			glBufferData(
				GL_ARRAY_BUFFER,
				sizeof(GLfloat) * 4,
				vectorVertexPairs[i],
				GL_DYNAMIC_DRAW
			);

			glUniform3f(
				uniformColorVariable,
				vectorRgbColors[i][0],
				vectorRgbColors[i][1],
				vectorRgbColors[i][2]
			);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, vectorVBOs[i]);
			glDrawArrays(GL_LINES, 0, 2);
		}

		this_thread::sleep_for(chrono::milliseconds(100));

		glfwSwapBuffers(window);
		glfwPollEvents();

		// actual physics done here, pretty underwhelming
		// compared to the absolute mountain of OpenGL calls
		velocity[Dim::Y] = (initialVelocityMagnitude * sin(theta)) - (gravitationalAcceleration * time);
		time += timeStep;



	} while (!glfwWindowShouldClose(window));
}

#endif