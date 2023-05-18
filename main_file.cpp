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
#include <glm/gtc/normalize.hpp>

ShaderProgram* sp;
WorldObject* ob;
Camera* cam;

float speed_x = 0; //angular speed in radians
float speed_y = 0; //angular speed in radians

//Error processing callback procedure
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
	float cameraSpeed = 0.05f; // Adjust this value to control camera movement speed

	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_W) // Move forward
			cam->position += cam->lookAt * cameraSpeed;
		if (key == GLFW_KEY_S) // Move backward
			cam->position -= cam->lookAt * cameraSpeed;
		if (key == GLFW_KEY_A) // Move left
			cam->position -= glm::normalize(glm::cross(cam->cameraFront, cam->cameraUp)) * cameraSpeed;
		if (key == GLFW_KEY_D) // Move right
			cam->position += glm::normalize(glm::cross(cam->cameraFront, cam->cameraUp)) * cameraSpeed;
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) speed_x = 0;
		if (key == GLFW_KEY_RIGHT) speed_x = 0;
		if (key == GLFW_KEY_UP) speed_y = 0;
		if (key == GLFW_KEY_DOWN) speed_y = 0;
	}
}


//Initialization code procedure
void initOpenGLProgram(GLFWwindow* window) {
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window,keyCallback);
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

	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Compute projection matrix
	glm::mat4 V = glm::lookAt(cam->position, cam->lookAt, cam->cameraUp); //Compute view matrix

	sp->use();
	//Send parameters to graphics card
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));

	ob->M = glm::mat4(1.0f);
	ob->M = glm::rotate(ob->M, angle_y, glm::vec3(1.0f, 0.0f, 0.0f)); //Compute model matrix
	ob->M = glm::rotate(ob->M, angle_x, glm::vec3(0.0f, 1.0f, 0.0f)); //
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(ob->M));

	glEnableVertexAttribArray(sp->a("vertex")); //Enable sending data to the attribute vertex
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0,static_cast<float*>( ob->vertices.data())); //Specify source of the data for the attribute vertex

	glDrawArrays(GL_TRIANGLES, 0, ob->vertCount);

	glDisableVertexAttribArray(sp->a("vertex")); //Disable sending data to the attribute vertex
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

	window = glfwCreateWindow(1280*2, 720*2, "OpenGL", NULL, NULL);  //Rozmiar HD (rozdzielczoœæ)   SPRAWDZIÆ NULLE!   Create a window 500pxx500px titled "OpenGL" and an OpenGL context associated with it.

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

	float angle_x = 0; //current rotation angle of the object, x axis
	float angle_y = 0; //current rotation angle of the object, y axis
	glfwSetTime(0);
	//Main application loop
	while (!glfwWindowShouldClose(window)) //As long as the window shouldnt be closed yet...
	{
		angle_x += speed_x * glfwGetTime(); //Add angle by which the object was rotated in the previous iteration
		angle_y += speed_y * glfwGetTime(); //Add angle by which the object was rotated in the previous iteration
		glfwSetTime(0); //Zero the timer
		drawScene(window, angle_x, angle_y); //Execute drawing procedure
		glfwPollEvents();//Process callback procedures corresponding to the events that took place up to now   SPRAWDZIÆ!!
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Delete OpenGL context and the window.
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}
