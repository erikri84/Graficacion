#pragma once

#include <iostream>
#include "Object3D.h"
#include "Plane.h"
#include "glm\mat4x4.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"


class Application {
public:
	Application();
	~Application();
	Plane oPlane;

	void setup();
	void update();
	GLuint initTexture(const std::string name);
	void display();
	void reshape(int w, int h);
	void loadShaders();
	void displayMiniMap();


private:	
	Object3D triangle;
	std::string strVertexShader, strFragmentShader;
	glm::mat4 rotation;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
	glm::mat4 camPers;
	glm::mat4 cam;
	glm::mat4 pers;

	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;

};

