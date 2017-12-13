
#include "Application.h"
#include <iostream>
#include <vector>

#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "ShaderFuncs.h"
#include "glm\vec3.hpp"
#include "SOIL.h"

//	- 0.75f, 0.75f, 0.75f, 1.0f,	// 0
//	-0.75f, -0.75f, 0.75f, 1.0f,	// 1
//	0.75f, -0.75f, 0.75f, 1.0f,		// 2
//	0.75f, 0.75f, 0.75f, 1.0f,		// 3
//	0.75f, -0.75f, -0.75f, 1.0f,	// 4
//	0.75f, 0.75f, -0.75f, 1.0f,		// 5
//	-0.75f, -0.75f, -0.75f, 1.0f,	// 6
//	-0.75f, 0.75f, -0.75f, 1.0f,	// 7
char laberynth[5][5] = 
{
	{1,1,1,1,1},
	{1,0,0,0,1},
	{1,1,0,1,1},
	{1,0,0,0,1},
	{1,1,1,1,1}
};

Application::Application() 
{}

Application::~Application() 
{}

GLuint Application::initTexture(const std::string name)
{
	int img_width, img_height;
	int channels;
	unsigned char* img = NULL;
	img = SOIL_load_image(name.c_str(), &img_width, &img_height, &channels, 0);
	GLuint id;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img);

	//glGenerateMipmap(GL_TEXTURE_2D);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//COMPORTAMIENTO LEJANO O CERCANO DE LOS VERTICES DE LA TEXU
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//FORMA EN LA QUE SE RECORTA LA TEXTURA
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBindTexture(GL_TEXTURE_2D, 0);
	return id;
}

void Application::setup()
{
    oPlane.createPlane(1); // AQUI DEBEN CREAR SU VERTEX ARRAY OBJECT Y SU VERTEX BUFFER OBJECT 
	loadShaders();
	
	oPlane.texture_id[0] = initTexture("nm0.jpg");
	oPlane.texture_id[1] = initTexture("nm1.jpg");

	InitializeProgram(oPlane.shader, strVertexShader, strFragmentShader);
	oPlane.uTransform[0] = glGetUniformLocation(oPlane.shader, "mTransform");
	/*oPlane.uEye[0] = glGetUniformLocation(oPlane.shader, "vEye");
	oPlane.uTime[0] = glGetUniformLocation(oPlane.shader, "fTime");*/
	oPlane.uTexture[0] = glGetUniformLocation(oPlane.shader, "textura0");
	oPlane.uTexture[1] = glGetUniformLocation(oPlane.shader, "textura1");

	eye = glm::vec3(100.0f, 100.0f, 0.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	glGenVertexArrays(1, &oPlane.vao);
	glBindVertexArray(oPlane.vao);
	glGenBuffers(1, &oPlane.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, oPlane.vbo);

	glBufferData(GL_ARRAY_BUFFER, oPlane.getVertexSizeInBytes() + oPlane.getTextureCoordsSizeInBytes(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, oPlane.getVertexSizeInBytes(), oPlane.plane); 
	glBufferSubData(GL_ARRAY_BUFFER, oPlane.getVertexSizeInBytes(), oPlane.getTextureCoordsSizeInBytes(), oPlane.textureCoords); 
	oPlane.cleanMemory();
	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)oPlane.getVertexSizeInBytes());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
}

void Application::update()
{
}


void Application::display()
{
	//Borramos el buffer de color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glUseProgram(oPlane.shader);
	glBindVertexArray(oPlane.vao);

	glm::mat4 myAllTransformations;
	rotationX = glm::rotate(glm::mat4(1.0f), (oPlane.fAngleX * 3.141592f / 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::mat4(1.0f), (oPlane.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::mat4(1.0f), (oPlane.fAngleZ * 3.141592f / 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotation = rotationX * rotationY * rotationZ;
	cam = glm::lookAt(eye, target, up);
	pers = glm::perspective(45.0f, (640.0f / 480.0f), 0.1f, 180.0f);
	rotation = pers * cam * rotation;

	glUseProgram(oPlane.shader);
	glUniformMatrix4fv(oPlane.uTransform[0], 1, GL_FALSE, glm::value_ptr(rotation));
	/*glUniform1f(oPlane.uTime[0], oPlane.time);
	glUniform1f(oPlane.uEye[0], oPlane.eye);*/

	// Texture 0 Lenna
	glBindTexture(GL_TEXTURE_2D, oPlane.texture_id[0]);
	glUniform1i(oPlane.uTexture[0], 0);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, oPlane.texture_id[1]);
	glUniform1i(oPlane.uTexture[1], 1);
	glActiveTexture(GL_TEXTURE1);

	// Texture 1 Firefox

	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());
}

void Application::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void Application::loadShaders()
{
	strVertexShader = loadTextFile("Shaders/BumpMapping.v");
	strFragmentShader = loadTextFile("Shaders/BumpMapping.f");
}

void Application::displayMiniMap()
{
	//Seleccionamos los shaders a usar
	glUseProgram(oPlane.shader);

	//activamos el vertex array object y dibujamos
	glBindVertexArray(oPlane.vao);

	/*rotationX = glm::rotate(glm::mat4(1.0f), (triangle.fAngleX * 3.141592f / 180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::mat4(1.0f), (triangle.fAngleY * 3.141592f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::mat4(1.0f), (triangle.fAngleZ * 3.141592f / 180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotation = rotationX * rotationY * rotationZ;*/
	eye = glm::vec3(0.0f, 20.0f, 5.0f);
	target = glm::vec3(0.0f, 0.0f, 10.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	cam = glm::lookAt(eye, target, up);
	pers = glm::perspective(45.0f, (640.0f / 480.0f), 0.1f, 20.0f);
	rotation = pers * cam;

	// Pasamos valiables a variables uniform
	glUniformMatrix4fv(oPlane.uTransform[0], // Variable Uniform que corresponde a la matriz
		1, // El arreglo de matrices solo tiene una matriz
		false, // No queremos que saque la transpuesta
		glm::value_ptr(rotation)); // Obtenemos el apuntador a los datos de la matriz

	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());
}
