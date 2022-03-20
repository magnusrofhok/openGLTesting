#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <cmath>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stack>
#include <SOIL2/SOIL2.h>

class Utils
{
public:
	static std::string readShaderSource(const char* filePath);
	static void printShaderLog(GLuint shader);
	static void printProgramLog(int prog);
	static bool checkOpenGLError();
	static GLuint createShaderProgram(const char* vp, const char* fp);
	glm::mat4 buildTranslate(float x, float y, float z);
	glm::mat4 buildRotateX(float rad);
	glm::mat4 buildRotateY(float rad);
	glm::mat4 buildRotateZ(float rad);
	glm::mat4 buildScale(float x, float y, float z);
	static GLuint loadTexture(const char *texImagePath);
	static float toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }


};

