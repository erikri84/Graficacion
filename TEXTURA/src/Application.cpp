
#include "Application.h"
#include <iostream>
#include <vector>

#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "ShaderFuncs.h"
#include "glm\vec3.hpp"
#include "SOIL.h"


Application::Application() 
{}

Application::~Application() 
{}

void Application::initTexture()
{
	// Soil pone la imagen de cabeza 
	int imgWidth, imgHeight, rgb;
	unsigned char* img = SOIL_load_image("sw.png", &imgWidth, &imgHeight, &rgb, 0);
	glGenTextures(1, &oPlane.texture_id);
	glBindTexture(GL_TEXTURE_2D, oPlane.texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img); // Liberamos la memoria del SOIL
	// Generate trilinear 
	//glGenerateMipmap(GL_TEXTURE_2D);
	// Trilinear filterin;
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Bilinear filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // RECORTA EN X
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // RECORTA EN Y

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::setup()
{
    oPlane.createPlane(1); // AQUI DEBEN CREAR SU VERTEX ARRAY OBJECT Y SU VERTEX BUFFER OBJECT 
	loadShaders();
	initTexture();
	InitializeProgram(oPlane.shader, strVertexShader, strFragmentShader);
	oPlane.uTransform[0] = glGetUniformLocation(oPlane.shader, "mTransform");
	/*oPlane.uEye[0] = glGetUniformLocation(oPlane.shader, "vEye");
	oPlane.uTime[0] = glGetUniformLocation(oPlane.shader, "fTime");*/
	oPlane.uTexture = glGetUniformLocation(oPlane.shader, "textura0");

	eye = glm::vec3(80.0f, 80.0f, 0.0f);
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
	oPlane.fAngleY = oPlane.fAngleY + 0.01f;
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
	glBindTexture(GL_TEXTURE_2D, oPlane.texture_id);
	glUniform1i(oPlane.uTexture, 0);
	glActiveTexture(GL_TEXTURE0);

	// Texture 1 Firefox

	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());
}

void Application::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void Application::loadShaders()
{
	strVertexShader = loadTextFile("Shaders/passThru.v");
	strFragmentShader = loadTextFile("Shaders/passThru.f");
}

