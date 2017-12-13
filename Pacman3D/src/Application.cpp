
#include "Application.h"
#include <iostream>
#include <vector>

#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "ShaderFuncs.h"
#include "glm\vec3.hpp"

//	- 1.0f, 1.0f, 1.0f, 1.0f,	// 0
//	-1.0f, -1.0f, 1.0f, 1.0f,	// 1
//	1.0f, -1.0f, 1.0f, 1.0f,		// 2
//	1.0f, 1.0f, 1.0f, 1.0f,		// 3
//	1.0f, -1.0f, -1.0f, 1.0f,	// 4
//	1.0f, 1.0f, -0.75f, 1.0f,		// 5
//	-0.75f, -0.75f, -0.75f, 1.0f,	// 6
//	-0.75f, 0.75f, -0.75f, 1.0f,	// 7
char laberynth[10][10] =  
{
//0==PACMAN
//1==MURO
//2==PELLET
//3==POWERUP
//4==GHOST
	//1 2  3  4  5  6  7  8  9  10
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//1
	{1, 0, 2, 2, 2, 2, 2, 2, 2, 1 },//2
	{1, 1, 1, 1, 2, 2, 1, 1, 1, 1 },//3
	{1, 2, 4, 1, 2, 2, 1, 2, 4, 1 },//4
	{1, 2, 3, 1, 2, 2, 1, 2, 3, 1 },//5
	{1, 2, 1, 1, 2, 2, 1, 1, 2, 1 },//6
	{1, 2, 2, 2, 2, 2, 2, 2, 2, 1 },//7
	{1, 2, 2, 2, 1, 1, 2, 2, 2, 1 },//8
	{1, 2, 2, 2, 2, 2, 2, 2, 2, 1 },//9
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }//10

};

GLfloat vertexPositions[] = {
	// Cara 1 (B1)
	-1.0f, 1.0f, 1.0f, 1.0f,		// 0
	-1.0f, -1.0f, 1.0f, 1.0f,	// 1
	1.0f, -1.0f, 1.0f, 1.0f,		// 2
	// Cara 1 (B2)
	-1.0f, 1.0f, 1.0f, 1.0f,		// 0
	1.0f, -1.0f, 1.0f, 1.0f,		// 2
	1.0f, 1.0f, 1.0f, 1.0f,		// 3
	// Cara 2 (C1)
	1.0f, 1.0f, 1.0f, 1.0f,		// 3
	1.0f, -1.0f, 1.0f, 1.0f,		// 2
	1.0f, -1.0f, -1.0f, 1.0f,	// 4
	// Cara 2 (C2)
	1.0f, 1.0f, 1.0f, 1.0f,		// 3
	1.0f, -1.0f, -1.0f, 1.0f,	// 4
	1.0f, 1.0f, -1.0f, 1.0f,		// 5
	// Cara 3 (D1)
	1.0f, 1.0f, -1.0f, 1.0f,		// 5
	1.0f, -1.0f, -1.0f, 1.0f,	// 4
	-1.0f, -1.0f, -1.0f, 1.0f,	// 6
	// Cara 3 (D2)
	1.0f, 1.0f, -1.0f, 1.0f,		// 5
	-1.0f, -1.0f, -1.0f, 1.0f,	// 6 
	-1.0f, 1.0f, -1.0f, 1.0f,	// 7
	// Cara 4 (A1)
	-1.0f, 1.0f, -1.0f, 1.0f,	// 7
	-1.0f, -1.0f, -1.0f, 1.0f,	// 6 
	-1.0f, -1.0f, 1.0f, 1.0f,	// 1
	// Cara 4 (A2)
	-1.0f, 1.0f, -1.0f, 1.0f,	// 7
	-1.0f, -1.0f, 1.0f, 1.0f,	// 1 
	-1.0f, 1.0f, 1.0f, 1.0f,		// 0
	// Cara 5 (E1)
	-1.0f, 1.0f, -1.0f, 1.0f,	// 7
	-1.0f, 1.0f, 1.0f, 1.0f,		// 0
	1.0f, 1.0f, 1.0f, 1.0f,		// 3
	// Cara 5 (E2)
	-1.0f, 1.0f, -1.0f, 1.0f,	// 7
	1.0f, 1.0f, 1.0f, 1.0f,		// 3
	1.0f, 1.0f, -1.0f, 1.0f,		// 5
	// Cara 6 (F1)
	-1.0f, -1.0f, 1.0f, 1.0f,	// 1 
	-1.0f, -1.0f, -1.0f, 1.0f,	// 6
	1.0f, -1.0f, -1.0f, 1.0f,	// 4
	// Cara 6 (F2)
	-1.0f, -1.0f, 1.0f, 1.0f,	// 1 
	1.0f, -1.0f, -1.0f, 1.0f,	// 4
	1.0f, -1.0f, 1.0f, 1.0f,		// 2
};


GLfloat vertexColors[] = {
	//Cara 1 VERDE
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,

	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	//Cara 2 ROJO
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	//Cara 3 AZÚL
	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,

	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	//Cara 4 NARANJA
	1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0,

	1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0,
	1.0, 0.3, 0.0, 1.0,
	//Cara 5 BLANCO
	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,

	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,
	//Cara 6 AMARILLO
	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,

	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
};

Application::Application() 
{}

Application::~Application() 
{}

void Application::setup()
{
	
	eye = glm::vec3(15.0f, 1.0f, 15.0f);
	target = glm::vec3(20.0f, 0.1, 20.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	alfa  = (0.0f);
	triangle.fAngleX = 0.0;
	triangle.fAngleY = 0.0;
	triangle.fAngleZ = 0.0;
	fpTrasX = 1.5f;
	fpTrasY = 0.0f;
	fpTrasZ = 1.5f;

	loadShaders();

	InitializeProgram(triangle.shader, strVertexShader, strFragmentShader);
	triangle.uniform = glGetUniformLocation(triangle.shader, "transform");//AQUI SE OBTIENE LAS VARIABLES UNIFORM
	triangle.uniformColor = glGetUniformLocation(triangle.shader, "cColor");


	triangle.numVertex = 36;
	glGenVertexArrays(1, &triangle.vao);
	glBindVertexArray(triangle.vao);
	glGenBuffers(1, &triangle.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions)+sizeof(vertexColors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0/*offset*/, sizeof(vertexPositions), vertexPositions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions), sizeof(vertexColors), vertexColors);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertexPositions));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Application::update()
{
	collissions();
	//triangle.fAngleX = triangle.fAngleX + 0.001f;
	//triangle.fAngleY = triangle.fAngleY + 0.001f;
	//triangle.fAngleZ = triangle.fAngleZ + 0.001f;
}


void Application::display()
{
	//Borramos el buffer de color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Seleccionamos los shaders a usar
	glUseProgram(triangle.shader);

	//activamos el vertex array object y dibujamos
	glBindVertexArray(triangle.vao);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(i*2.0f, 0.0f, j*2.0f));
			if (on)//SE ACTIVA LA CAMARA FPS
			{

				tempMatrixCam = glm::lookAt(eye, target, up);
				pers = glm::perspective(45.0f, (640.0f / 480.0f), 0.1f, 40.0f);
				cam = pers * tempMatrixCam;

			}

			else//SE ACTIVA LA CAMARA ORTOGONAL
			{
				rotateZ = glm::rotate(glm::mat4(1.0f), (-3.14f / 2), glm::vec3(1.0f, 0.0f, 0.0f));
				tempOrthoCam = glm::ortho(-1.0f,19.0f, -1.0f, 19.0f);
				cam = tempOrthoCam * rotateZ;
			}

			if (laberynth[j][i] == 0)
			{
				esc = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5));
				trans = glm::translate(glm::mat4(1.0f), glm::vec3(fpTrasX * j, fpTrasY, fpTrasZ * i));
				myTrans = cam * trans * esc;

				glUniform4fv(triangle.uniformColor, 1, glm::value_ptr(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)));
				glUniformMatrix4fv(triangle.uniform, // Variable Uniform que corresponde a la matriz
					1, // El arreglo de matrices solo tiene una matriz
					false, // No queremos que saque la transpuesta
					glm::value_ptr(rotation)); // Obtenemos el apuntador a los datos de la matriz
				glDrawArrays(GL_TRIANGLES, 0, triangle.numVertex);
			}
			else if (laberynth[j][i] == 1)
			{
				rotation = cam * trans;

				// Pasamos valiables a variables uniform
				glUniform4fv(triangle.uniformColor, 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)));
				glUniformMatrix4fv(triangle.uniform, // Variable Uniform que corresponde a la matriz
					1, // El arreglo de matrices solo tiene una matriz
					false, // No queremos que saque la transpuesta
					glm::value_ptr(rotation)); // Obtenemos el apuntador a los datos de la matriz
				glDrawArrays(GL_TRIANGLES, 0, triangle.numVertex);
			}

			else if (laberynth[j][i] == 2)
			{
			    esc = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f));

				rotation = cam * trans * esc;
				glUniform4fv(triangle.uniformColor, 1, glm::value_ptr(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)));//COLOR DE LA GEOMETRIA
				glUniformMatrix4fv(triangle.uniform, // Variable Uniform que corresponde a la matriz
					1, // El arreglo de matrices solo tiene una matriz
					false, // No queremos que saque la transpuesta
					glm::value_ptr(rotation)); // Obtenemos el apuntador a los datos de la matriz
				glDrawArrays(GL_TRIANGLES, 0, triangle.numVertex);
			}

			else if (laberynth[j][i] == 3)
			{
				esc = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.4f, 0.4f));

				rotation = pers * cam * trans * esc;
				glUniform4fv(triangle.uniformColor, 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
				glUniformMatrix4fv(triangle.uniform, // Variable Uniform que corresponde a la matriz
					1, // El arreglo de matrices solo tiene una matriz
					false, // No queremos que saque la transpuesta
					glm::value_ptr(rotation)); // Obtenemos el apuntador a los datos de la matriz
				glDrawArrays(GL_TRIANGLES, 0, triangle.numVertex);
			}

			else if (laberynth[j][i] == 4)
			{

			}
		}
	}
}

void Application::collissions() 
{
	if (on)
	{
		float posEyeSavedX = eye.x;
		float posEyeSavedZ = eye.z;
		float posTarSavedX = target.x;
		float posTarSavedZ = target.z;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				float distWithCubes = glm::sqrt(((eye.x - (j * 2.0f)) * (eye.x - (j * 2.0f))) + ((eye.z - (i * 2.0f)) * (eye.z - (i * 2.0f))));
				if (distWithCubes < 100.1f)
				{
					if (laberynth[j][i] == 0)
					{
						eye.x = posEyeSavedX;
						eye.z = posEyeSavedZ;
						target.x = posTarSavedX;
						target.z = posTarSavedZ;
					}
					else if (laberynth[j][i] == 2)
					{
						laberynth[j][i] == 4;
					}
					else if (laberynth[j][i] == 3)
					{
						laberynth[j][i] == 4;
					}
				}
			}
		}
	}
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
