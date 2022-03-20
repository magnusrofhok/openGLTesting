#include "Sphere.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include "Utils.h"

Sphere::Sphere()
{
	init(48);
}

Sphere::Sphere(int prec)
{
	init(prec);
}

void Sphere::init(int prec)
{
	numVertices = (prec + 1) * (prec + 1);
	numIndices = prec * prec * 6;
	for (int i = 0; i < numVertices; i++) { vertices.push_back(glm::vec3()); }
	for (int i = 0; i < numVertices; i++) { texCoords.push_back(glm::vec2()); }
	for (int i = 0; i < numVertices; i++) { normals.push_back(glm::vec3()); }
	for (int i = 0; i < numIndices; i++) { indices.push_back(0); }

	//triangle vertices calculated

	for (int i = 0; i <= prec; i++)
	{
		for (int j = 0; j <= prec; j++)
		{
			float y = (float)cos(Utils::toRadians(180.0f - i * 180.0f / prec));
			float x = -(float)cos(Utils::toRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
			float z = (float)sin(Utils::toRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
			vertices[i * (prec + 1) + j] = glm::vec3(x, y, z);
			texCoords[i * (prec + 1) + j] = glm::vec2(((float)j / prec), ((float)i / prec));
			normals[i * (prec + 1) + j] = glm::vec3(x, y, z);
			// calculate tangent vector
			/*if (((x == 0) && (y == 1) && (z == 0)) || ((x == 0) && (y == -1) && (z == 0)))
			{
				tangents[i * (prec + 1) + j] = glm::vec3(0.0f, 0.0f, -1.0f);
			}
			else 
			{
				tangents[i * (prec + 1) + j] = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(x, y, z));
			}*/
		}
	}

	//triangle indices calculated

	for (int i = 0; i < prec; i++)
	{
		for (int j = 0; j < prec; j++)
		{
			indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
			indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
			indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
			indices[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;
		}
	}
}

//getter functions:

int Sphere::getNumVertices() { return numVertices; }
int Sphere::getNumIndices() { return numIndices; }
std::vector<int> Sphere::getIndices() { return indices; }
std::vector<glm::vec3> Sphere::getVertices() { return vertices; }
std::vector<glm::vec2> Sphere::getTexCoords() { return texCoords; }
std::vector<glm::vec3> Sphere::getNormals() { return normals; }

