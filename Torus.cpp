#include <cmath>
#include <vector>
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include "Torus.h"
#include "Utils.h"

Torus::Torus()
{
	prec = 48;
	inner = 0.5f;
	outer = 0.2f;
	init();
}

Torus::Torus(float innerRadius, float outerRadius, int precIn)
{
	prec = precIn;
	inner = innerRadius;
	outer = outerRadius;
	init();
}

void Torus::init()
{
	numVertices = (prec + 1) * (prec + 1);
	numIndices = prec * prec * 6;
	for (int i = 0; i < numVertices; i++) { vertices.push_back(glm::vec3()); }
	for (int i = 0; i < numVertices; i++) { texCoords.push_back(glm::vec2()); }
	for (int i = 0; i < numVertices; i++) { normals.push_back(glm::vec3()); }
	for (int i = 0; i < numVertices; i++) { sTangents.push_back(glm::vec3()); }
	for (int i = 0; i < numVertices; i++) { tTangents.push_back(glm::vec3()); }
	for (int i = 0; i < numIndices; i++) { indices.push_back(0); }

	//calculate the first ring
	for (int i = 0; i < prec + 1; i++)
	{
		float amt = Utils::toRadians(i * 360.0f / prec);

		//building the ring, rotating points around origin, then moving them outward
		glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::vec3 initPos(rMat * glm::vec4(outer, 0.0f, 0.0f, 1.0f));
		vertices[i] = glm::vec3(initPos + glm::vec3(inner, 0.0f, 0.0f));
		
		//compute tex coords for each vertex
		texCoords[i] = glm::vec2(0.0f, ((float)i / (float)prec));

		//compute tangents and normals, first is Y-axis rotated around Z
		rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));
		tTangents[i] = glm::vec3(rMat * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));
		sTangents[i] = glm::vec3(glm::vec3(0.0f, 0.0f, -1.0f));
		normals[i] = glm::cross(tTangents[i], sTangents[i]);
	}

	//rotate the first ring about Y to get the other
	for (int ring = 1; ring < prec + 1; ring++)
	{
		for (int vert = 0; vert < prec + 1; vert++)
		{
			//vertex pos
			float amt = (float)(Utils::toRadians(ring * 360.0f / prec));
			glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
			vertices[ring * (prec + 1) + vert] = glm::vec3(rMat * glm::vec4(vertices[vert], 1.0f));

			// tex coords new rings
			texCoords[ring * (prec + 1) + vert] = glm::vec2((float)ring * 2.0f / (float)prec, texCoords[vert].t);
			if (texCoords[ring * (prec + 1) + vert].s > 1.0) texCoords[ring * (prec + 1) + vert].s -= 1.0f;

			//rotate the tangent
			rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
			sTangents[ring * (prec + 1) + vert] = glm::vec3(rMat * glm::vec4(sTangents[vert], 1.0f));
			rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
			tTangents[ring * (prec + 1) + vert] = glm::vec3(rMat * glm::vec4(tTangents[vert], 1.0f));

			//rotate normal vector aorund the Y axis
			rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
			normals[ring * (prec + 1) + vert] = glm::vec3(rMat * glm::vec4(normals[vert], 1.0f));
		}
	}
	
	//calculate triangle indices for the two triangles per vertex
	for (int ring = 0; ring < prec; ring++)
	{
		for (int vert = 0; vert < prec; vert++)
		{
			indices[((ring * prec + vert) * 2) * 3 + 0] = ring * (prec + 1) + vert;
			indices[((ring * prec + vert) * 2) * 3 + 1] = (ring + 1) * (prec + 1) + vert;
			indices[((ring * prec + vert) * 2) * 3 + 2] = ring * (prec + 1) + vert + 1;
			indices[((ring * prec + vert) * 2 + 1) * 3 + 0] = ring * (prec + 1) + vert + 1;
			indices[((ring * prec + vert) * 2 + 1) * 3 + 1] = (ring + 1) * (prec + 1) + vert;
			indices[((ring * prec + vert) * 2 + 1) * 3 + 2] = (ring + 1) * (prec + 1) + vert + 1;
		}
	}
}

//getter functions

int Torus::getNumVertices() { return numVertices; }
int Torus::getNumIndices() { return numIndices; }
std::vector<int> Torus::getIndices() { return indices; }
std::vector<glm::vec3> Torus::getVertices() { return vertices; }
std::vector<glm::vec2> Torus::getTexCoords() { return texCoords; }
std::vector<glm::vec3> Torus::getNormals() { return normals; }
std::vector<glm::vec3> Torus::getSTangents() { return sTangents; }
std::vector<glm::vec3> Torus::getTtangents() { return tTangents; }