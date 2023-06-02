#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

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
//#include "myCube.h"

#include "WorldObject.h"
#include <iostream>
#include "Camera.h"
#include "Scene.h"
#include <glm/gtx/normal.hpp>

ShaderProgram* sp;
Scene * scene;
Player* player;

//glm::vec3 pos = glm::vec3(0, 1, -5);
//glm::vec3 dir = glm::vec3(0, 0, 1);


//float speed_x = 0; //angular speed in radians
//float speed_y = 0; //angular speed in radians
//float ws = 0;
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
		if (key == GLFW_KEY_LEFT) player->left();
		if (key == GLFW_KEY_RIGHT) player->right();
		//if (key == GLFW_KEY_PAGE_UP) cam->speed_x = 1;
		//if (key == GLFW_KEY_PAGE_DOWN) cam->speed_x = -1;
		if (key == GLFW_KEY_UP) player->ws = 1;
		if (key == GLFW_KEY_DOWN) player->ws = -1;
	}
	if (action == GLFW_RELEASE) {
		
		if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT)player->turnStop();

		if (key == GLFW_KEY_UP) player->ws = 0;
		if (key == GLFW_KEY_DOWN) player->ws = 0;

		//if (key == GLFW_KEY_PAGE_UP) cam->speed_x = 0;
		//if (key == GLFW_KEY_PAGE_DOWN) cam->speed_x = -0;
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
	scene = new Scene("alley");
	scene->loadLevel();
	player = new Player();
}

//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
	scene->clean();
	delete player;
	delete scene;
	delete sp;
	//************Place any code here that needs to be executed once, after the main loop ends************
}


void drawScene(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // SPRAWDZIÆ!!

	glm::mat4 V = glm::lookAt(player->cam->position, player->cam->position + player->cam->dir, glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 0.1f, 50.0f); //Wylicz macierz rzutowania

	//Send parameters to graphics card
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));

	scene->draw(sp);

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
		
		player->update(glfwGetTime());
		glfwSetTime(0); //Zero the timer
		drawScene(window); //Execute drawing procedure
		glfwPollEvents();//Process callback procedures corresponding to the events that took place up to now   SPRAWDZIÆ!!
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Delete OpenGL context and the window.
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}
