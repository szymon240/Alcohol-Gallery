#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include "myTeapot.h"
#include "WorldObject.h"
#include <iostream>
#include "Camera.h"
#include <glm/gtx/normal.hpp>

ShaderProgram* sp;
WorldObject* ob;
Camera* cam;

//glm::vec3 pos = glm::vec3(0, 1, -5);
//glm::vec3 dir = glm::vec3(0, 0, 1);


//float speed_x = 0; //angular speed in radians
//float speed_y = 0; //angular speed in radians
float ws = 0;
//Error processing callback procedure
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(
	GLFWwindow* window,
	int key,
	int scancode,
	int action,
	int mod
) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) cam->speed_y = 1;
		if (key == GLFW_KEY_RIGHT) cam->speed_y = -1;
		if (key == GLFW_KEY_PAGE_UP) cam->speed_x = 1;
		if (key == GLFW_KEY_PAGE_DOWN) cam->speed_x = -1;
		if (key == GLFW_KEY_UP) ws = 1;
		if (key == GLFW_KEY_DOWN) ws = -1;
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) cam->speed_y = 0;
		if (key == GLFW_KEY_RIGHT) cam->speed_y = 0;

		if (key == GLFW_KEY_UP) ws = 0;
		if (key == GLFW_KEY_DOWN) ws = 0;

		if (key == GLFW_KEY_PAGE_UP) cam->speed_x = 0;
		if (key == GLFW_KEY_PAGE_DOWN) cam->speed_x = -0;
	}
}
//Pro


//Initialization code procedure
void initOpenGLProgram(GLFWwindow* window) {
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window,keyCallback);
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
	ob = new WorldObject("objects/Cubone/modell.obj");
	cam = new Camera();
}

//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
	delete ob;
	//************Place any code here that needs to be executed once, after the main loop ends************
}


void drawScene(GLFWwindow* window, float angle_x, float angle_y) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // SPRAWDZIÆ!!

	glm::mat4 V = glm::lookAt(cam->position, cam->position + cam->dir, glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 0.1f, 50.0f); //Wylicz macierz rzutowania

	//Send parameters to graphics card
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));

	ob->draw(sp);

	glfwSwapBuffers(window); //Copy back buffer to front buffer
}

int main(void)
{
	GLFWwindow* window; //Pointer to object that represents the application window

	glfwSetErrorCallback(error_callback);//Register error processing callback procedure

	if (!glfwInit()) { //Initialize GLFW library
		fprintf(stderr, "Can't initialize GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1920, 720*2, "OpenGL", NULL, NULL);  //Rozmiar HD (rozdzielczoœæ)   SPRAWDZIÆ NULLE!   Create a window 500pxx500px titled "OpenGL" and an OpenGL context associated with it.

	if (!window) //If no window is opened then close the program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Since this moment OpenGL context corresponding to the window is active and all OpenGL calls will refer to this context.
	glfwSwapInterval(1); //During vsync wait for the first refresh

	GLenum err;
	if ((err=glewInit()) != GLEW_OK) { //Initialize GLEW library
		fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Call initialization procedure

	//float angle_x = 0; //current rotation angle of the object, x axis
	//float angle_y = 0; //current rotation angle of the object, y axis
	glfwSetTime(0);
	//Main application loop
	while (!glfwWindowShouldClose(window)) //As long as the window shouldnt be closed yet...
	{
		cam->angle_x += cam->speed_x * glfwGetTime(); //Add angle by which the object was rotated in the previous iteration
		cam->angle_y += cam->speed_y * glfwGetTime(); //Add angle by which the object was rotated in the previous iteration

		cam->position += ws * (float)glfwGetTime() * cam->update();
		glfwSetTime(0); //Zero the timer
		drawScene(window, cam->angle_x, cam->angle_y); //Execute drawing procedure
		glfwPollEvents();//Process callback procedures corresponding to the events that took place up to now   SPRAWDZIÆ!!
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Delete OpenGL context and the window.
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}
