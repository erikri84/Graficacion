#pragma once

#include <iostream>
#include "Object3D.h"

class Application {
public:
	Application();
	~Application();

	void setup();
	void display();
	void reshape(int w, int h);


private:	
	Object3D triangle;
};

