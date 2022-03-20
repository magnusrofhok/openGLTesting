#pragma once
#include "Utils.h"
#include "Sphere.h"
#include "Torus.h"
#include "ImportedModel.h"

#define numVAOs 1
#define numVBOs 4
float cameraX, cameraY, cameraZ;
//float cubeLocX, cubeLocY, cubeLocZ;
//float pyrLocX, pyrLocY, pyrLocZ;
//float sphLocX, sphLocY, sphLocZ;
float torLocX, torLocY, torLocZ;
float modelLocX, modelLocY, modelLocZ;


GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];
GLuint brickTexture, skyTexture, earthTexture, shuttleTexture;;
GLuint mvLoc, tfLoc, projLoc;
int width, height;
float aspect, timeFactor, rotAmt = 0.0f;;
glm::mat4 pMat, vMat, mMat, mvMat, rMat, tMat;
std::stack<glm::mat4> mvStack;

ImportedModel myModel("data/objects/shuttle.obj");

//Sphere mySphere = Sphere(48);
//Torus myTorus(0.5f, 0.2f, 48);
Torus myTorus = Torus(0.5f, 0.2f, 48);
//Torus myTorus;

void setupVertices(void)
{
	//New Objects stuff
	
	/*std::vector<glm::vec3> vert = myModel.getVertices();
	
	std::vector<glm::vec2> tex = myModel.getTextureCoords();
	std::vector<glm::vec3> norm = myModel.getNormals();
	int numObjVertices = myModel.getNumVertices();
	
	std::vector<float> pValues;
	std::vector<float> tValues;
	std::vector<float> nValues;
	std::cout << numObjVertices << std::endl;
	for (int i = 0; i < numObjVertices; i++)
	{
		std::cout << " 3" << std::endl;
		pValues.push_back((vert[i]).x);
		pValues.push_back((vert[i]).y);
		pValues.push_back((vert[i]).z);

		tValues.push_back((tex[i]).s);
		tValues.push_back((tex[i]).t);

		nValues.push_back((norm[i]).x);
		nValues.push_back((norm[i]).y);
		nValues.push_back((norm[i]).z);
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pValues.size() * 4, &pValues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tValues.size() * 4, &tValues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nValues.size() * 4, &nValues[0], GL_STATIC_DRAW);
	*/

	//new Torus Stuff:

	std::vector<int> ind = myTorus.getIndices();
	std::vector<glm::vec3> vert = myTorus.getVertices();
	std::vector<glm::vec2> tex = myTorus.getTexCoords();
	std::vector<glm::vec3> norm = myTorus.getNormals();
	
	std::vector<float> pValues;
	std::vector<float> tValues;
	std::vector<float> nValues;

	int numVertices = myTorus.getNumVertices();
	std::cout << numVertices << std::endl;
	for (int i = 0; i < numVertices; i++)
	{
		pValues.push_back(vert[i].x);
		pValues.push_back(vert[i].y);
		pValues.push_back(vert[i].z);

		tValues.push_back(tex[i].s);
		tValues.push_back(tex[i].t);

		nValues.push_back(norm[i].x);
		nValues.push_back(norm[i].y);
		nValues.push_back(norm[i].z);
		
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pValues.size() * 4, &pValues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tValues.size() * 4, &tValues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nValues.size() * 4, &nValues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, &ind[0], GL_STATIC_DRAW);
	
	//old Sphere Stuff:

	//std::vector<int> ind = mySphere.getIndices();
	//std::vector<glm::vec3> vert = mySphere.getVertices();
	//std::vector<glm::vec2> tex = mySphere.getTexCoords();
	//std::vector<glm::vec3> norm = mySphere.getNormals();
	//
	//std::vector<float> pValues;
	//std::vector<float> tValues;
	//std::vector<float> nValues;
	//int numIndices = mySphere.getNumIndices();

	//for (int i = 0; i < numIndices; i++)
	//{
	//	pValues.push_back((vert[ind[i]]).x);
	//	pValues.push_back((vert[ind[i]]).y);
	//	pValues.push_back((vert[ind[i]]).z);

	//	tValues.push_back((tex[ind[i]]).s);
	//	tValues.push_back((tex[ind[i]]).t);

	//	nValues.push_back((norm[ind[i]]).x);
	//	nValues.push_back((norm[ind[i]]).y);
	//	nValues.push_back((norm[ind[i]]).z);
	//}

	//glGenVertexArrays(1, vao);
	//glBindVertexArray(vao[0]);
	//glGenBuffers(numVBOs, vbo);

	//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, pValues.size() * 4, &pValues[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//glBufferData(GL_ARRAY_BUFFER, tValues.size() * 4, &tValues[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	//glBufferData(GL_ARRAY_BUFFER, nValues.size() * 4, &nValues[0], GL_STATIC_DRAW);
}

void init(GLFWwindow* window)
{
	renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 1.0f;
	//sphLocX = 0.0f; sphLocY = 0.0f; sphLocZ = -1.0f;
	torLocX = 0.0f; torLocY = 0.0f; torLocZ = -0.5f;
	modelLocX = 0.0f; modelLocY = 0.0f; modelLocZ = 0.0f;
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
	
	
	//cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;
	//pyrLocX = 2.0f; pyrLocY = 2.0f; pyrLocZ = 0.0f;
	setupVertices();
	brickTexture = Utils::loadTexture("data/images/brick256.jpg");
	skyTexture = Utils::loadTexture("data/images/sky.jpg");
	earthTexture = Utils::loadTexture("data/images/earth.jpg");
	shuttleTexture = Utils::loadTexture("data/images/spstob_1.jpg");
}

void display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	//view matrix --------------------------
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
		
	//Model
	//mMat = glm::translate(glm::mat4(1.0f), glm::vec3(modelLocX, modelLocY, modelLocZ));
	//
	//mMat = glm::rotate(mMat, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//mMat = glm::rotate(mMat, Utils::toRadians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//mMat = glm::rotate(mMat, Utils::toRadians(35.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	////rotation, rotAmt = speed, -0.45f = angle
	///*rotAmt += 0.0018f;
	//mMat = glm::rotate(mMat, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//mMat = glm::rotate(mMat, rotAmt, glm::vec3(0.0f, 1.0f, 0.0f));
	//mMat = glm::rotate(mMat, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));*/

	//mvMat = vMat * mMat;

	//glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(1);


	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, shuttleTexture);
	//
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	//glDrawArrays(GL_TRIANGLES, 0, myModel.getNumVertices());



	//Torus

	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(torLocX, torLocY, torLocZ));
	mMat = glm::rotate(mMat, Utils::toRadians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	////rotation, rotAmt = speed, -0.45f = angle
	rotAmt += 0.0018f;
	mMat = glm::rotate(mMat, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	mMat = glm::rotate(mMat, rotAmt, glm::vec3(0.0f, 1.0f, 0.0f));
	mMat = glm::rotate(mMat, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

	mvMat = vMat * mMat;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
		

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, brickTexture);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, myTorus.getNumIndices(), GL_UNSIGNED_INT, 0);

	//std::cout << mvMat.length() << std::endl;
	
	////sphere
	//mMat = glm::translate(glm::mat4(1.0f), glm::vec3(sphLocX, sphLocY, sphLocZ));

	////rotation, rotAmt = speed, -0.45f = angle
	//rotAmt += 0.0018f;
	//mMat = glm::rotate(mMat, -0.45f, glm::vec3(1.0f, 0.0f, 0.0f));
	//mMat = glm::rotate(mMat, rotAmt, glm::vec3(0.0f, 1.0f, 0.0f));
	//mMat = glm::rotate(mMat, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

	//mvMat = vMat * mMat;
	//
	//glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(1);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, earthTexture);
	//
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//
	//
	//glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
	
	//pyramid sun buffer #1 -----------------------------------
	
	//mvStack.push(mvStack.top());
	//mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	//mvStack.push(mvStack.top());
	//mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));

	//glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));

	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	//glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
	//glEnableVertexAttribArray(1);
	//

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	//glFrontFace(GL_CCW);
	//glDrawArrays(GL_TRIANGLES, 0, 18);
	//mvStack.pop();

	////cube planet buffer #0 -----------------------------------
	//
	//mvStack.push(mvStack.top());
	//mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime) * 4.0, 0.0f, cos((float)currentTime) * 4.0));
	//mvStack.push(mvStack.top());
	//mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.25f, 1.0f, 0.0f));

	//glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	//		
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	//glEnableVertexAttribArray(0);

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, skyTexture);


	//glFrontFace(GL_CW);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//mvStack.pop();

	////small planet buffer #0 -----------------------------------

	//mvStack.push(mvStack.top());
	//mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin((float)currentTime) * 2.0, cos((float)currentTime) * 2.0));
	//mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
	//mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25, 0.25f));

	//glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));

	//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	//glEnableVertexAttribArray(0);

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	//glFrontFace(GL_CW);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//mvStack.pop(); mvStack.pop(); mvStack.pop(); mvStack.pop();

	
}

void window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight)
{
	aspect = (float)newWidth / (float)newHeight;
	glViewport(0, 0, newWidth, newHeight);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

int main(void)
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Testing", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	glfwSetWindowSizeCallback(window, window_reshape_callback);

	init(window);
	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

