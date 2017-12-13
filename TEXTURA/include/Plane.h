#pragma once

#include "Object3D.h"
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Plane : public Object3D
{
public:
	GLfloat *normals,
			*plane,
			*textureCoords;

	Plane();
	~Plane();

	glm::vec3 aRotations;
	glm::mat4 mTransform;


	GLint uTransform[2];
	GLint uTime[2];
	GLint uEye[2];
	GLuint texture_id;
	GLint uTexture;

	size_t size;

	void createPlane(int side = 100);
	void cleanMemory();
	int getNumVertex();
		
	int side;

	size_t getVertexSizeInBytes();
	size_t getTextureCoordsSizeInBytes();
	
};