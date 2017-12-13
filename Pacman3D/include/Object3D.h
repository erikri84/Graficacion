#pragma once

#include <iostream>
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

class Object3D{
public:
	GLuint	vao, //Vertex Array Object
			vbo; //Vertex Buffer Object
	float time; 
	float eye;
	int numVertex; //numero de vertices para este objeto

	GLuint shader; //referencia a los shaders
	GLuint uniform, uniformColor; // Para almacenar el ángulo
	float fAngle;
	float fAngleX, fAngleY, fAngleZ;
};

