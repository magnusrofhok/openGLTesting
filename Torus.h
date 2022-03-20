#pragma once
#include <cmath>
#include <vector>
#include <glm/glm.hpp>


class Torus
{
private:
	int numVertices;
	int numIndices;
	int prec;
	float inner;
	float outer;
	std::vector<int>indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> sTangents;
	std::vector<glm::vec3> tTangents;
	void init();

public:
	Torus();
	Torus(float innerRadius, float outerRadius, int precIn);
	int getNumVertices();
	int getNumIndices();
	std::vector<int> getIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec2> getTexCoords();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec3> getSTangents();
	std::vector<glm::vec3> getTtangents();

};

