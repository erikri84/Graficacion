#pragma once

#include <iostream>
#include "Object3D.h"
#include "Plane.h"
#include "glm\mat4x4.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"


class Application {
public:
	bool on = true;
	Application();
	~Application();
	Plane oPlane;

	void setup();
	void update();
	void display();
	void reshape(int w, int h);
	void loadShaders();
	void displayMiniMap();
	void collissions();

	float fpTras;
	float fpTrasX;
	float fpTrasY;
	float fpTrasZ;
	float alfa;

	glm::mat4 fpRotation;
	glm::mat4 fpRotationX;
	glm::mat4 fpRotationY;
	glm::mat4 fpRotationZ;

	glm::vec4 fpRot;
	glm::vec3 fpEye;
	glm::vec3 fpTarget;
	glm::vec3 fpUp;
	
	Object3D triangle;
	Object3D walls;
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

	glm::mat4 esc;
	glm::mat4 tempMatrixCam;
	glm::mat4 tempOrthoCam;
	glm::mat4 myTrans;
	glm::mat4 rotateZ;
	glm::mat4 trans;

};

