#include <iostream>	

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "AppModules.h"

#include <conio.h>

#include <thread>
#include <chrono>

#pragma comment(lib, "glew32")
#pragma comment(lib, "glfw3dll")

using namespace std;
using namespace glm;

const char* FRAGMENT_SHADER_SRC = R"(#version 330 core
uniform vec3 inColor;
out vec3 outColor;
void main() {
	outColor = inColor;
}
)";

const char* VERTEX_SHADER_SRC = R"(#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
void main() {
	gl_Position.xyz = vertexPosition_modelspace;
	gl_Position.w = 1.0;
}
)";

static void openglMain() {
	if (!glfwInit()) {
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(720, 480, "Hello?", NULL, NULL);

	if (!window) {
		printf("Window Failed\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		return;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//
	// Vertex / Fragment shader compilation
	//

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
		return;
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
		return;
	}

	//
	// Shader program linking
	//

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
		return;
	}

	glUseProgram(programId);
	
	//
	// Shader Cleanup
	//

	glDetachShader(programId, vertexShaderId);
	glDetachShader(programId, fragmentShaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	//
	// Vertex Array Setup
	//

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//
	// Vertex Buffer Setup
	//

	// 0 -> vector all comp
	// 1 -> vector horizontal comp
	// 2 -> vector vertical comp
	GLfloat vectorVertexPairs[3][4] = {
		{0, 0, 1, 1},
		{0, 0, -1, -1},
		{0, 0, -1, 1},
	};

	GLfloat vectorRgbColors[3][3] = {
		{ 1, 1, 1 }, // white
		{ 1, 0, 0 }, // red
		{ 0, 0, 1 }	 // blue	
	};

	GLuint vectorVBOs[3];
	glGenBuffers(3, vectorVBOs);

	//
	// Frame Render Loop
	//
	
	GLfloat scale = 100.f;

	GLuint uniformColorVariable = glGetUniformLocation(programId, "inColor");

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
	} while (!glfwWindowShouldClose(window));
}

int main() {
	GLFWwindow* window = graphicsInit();
	if (!window) {
		return -1;
	}
	projectileMotionApp(window);
}