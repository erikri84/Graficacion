
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <conio.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Application.h"

Application app;
int timer = 0;
float alfa = 0;
float vel = 0.0001;

//Se tiene que llamar despues de inicializar la ventana y el OpenGL, pero antes del main loop
void setup()
{
	app.setup();
}

//Se ejecuta siempre que se necesite actualizar la imagen
void display()
{
	app.display();
}

//Se ejecuta cuando la ventana cambia de tamaño. Parámetros en pixeles.
//(ojo: En otros programas se debe ejecutar glViewport)
void reshape(int w, int h)
{
	app.reshape(w, h);
}


int main(int argc, char *argv[])
{
	//Application app;

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE; 
	glewInit();
	app.setup();

	// get version info 
	const GLubyte* renderer = glGetString (GL_RENDERER); 
	const GLubyte* version = glGetString (GL_VERSION); 
	printf (" Renderer: %s\ n", renderer); 
	printf (" OpenGL version supported %s\ n", version); 
	
	// tell GL to only draw onto a pixel if the shape is closer to the viewer 
	//glEnable (GL_DEPTH_TEST); // enable depth-testing 	
	//glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer" 

	glViewport(0, 0, (GLsizei)640, (GLsizei)480);
	glEnable(GL_DEPTH_TEST); // Habilita el z-buffer

	while (!glfwWindowShouldClose(window))
	{
		/* update other events like input handling */
		glfwPollEvents();

		// Update de Application
		app.update();

		/* put the stuff we've been drawing onto the display */
		app.display();

		//TECLADO, SWITCH Y MOUSE
		//char key;
		//key = _getch();
		//if (key == 'v')
		//	app.on = false;

		//if (key == 'c')
		//	app.on = true;

		glfwSwapBuffers(window);

		if (glfwGetKey(window, GLFW_KEY_V))
		{
			app.on = false;
		}

		if (glfwGetKey(window, GLFW_KEY_B))
		{
			app.on = true;
		}

		if (glfwGetKey(window, GLFW_KEY_A))
		{
			if (alfa < 90.0f)
			{
				//app.target.x += 0.01f;
				app.target.z += 0.1f;
				alfa = 180.0f;
			}

			else if (alfa < 180.0f)
			{
				//app.target.x += 0.01f;
				app.target.z += 0.01f;
				alfa = alfa + 90.0f;
			}

			else if (alfa < 270.0f)
			{
				//app.target.x -= 0.01f;
				app.target.z -= 0.01f;
				alfa = alfa + 90.0f;
			}

			else if (alfa < 360.0f)
			{
				//app.target.x -= 0.01f;
				app.target.z -= 0.01f;
				//alfa = 90.0f;
			}

		
			else
				alfa = 0;
			printf("Angulo: %f\n", alfa);
		}

		if (glfwGetKey(window, GLFW_KEY_W))
		{
			app.eye.x += (app.target.x - app.eye.x) * vel;
			app.eye.z += (app.target.z - app.eye.z) * vel;
			app.target.x += (app.target.x + app.eye.x) * vel;
			app.target.z += (app.target.z - app.eye.z) * vel;
		}

		if (glfwGetKey(window, GLFW_KEY_S))
		{
			app.eye.x -= (app.target.x - app.eye.x) * vel;
			app.eye.z -= (app.target.z - app.eye.z) * vel;
			app.target.x -= (app.target.x - app.eye.x) * vel;
			app.target.z -= (app.target.z - app.eye.z) * vel;
		}
	}

	/* close GL context and any other GLFW resources */
	glfwTerminate();
	return 0;

}
