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
#include "WorldObject.h"
#include <iostream>
#include "Camera.h"
#include "Scene.h"
#include <glm/gtx/normal.hpp>

ShaderProgram* sp;
Scene * scene;
Player* player;

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
		if (key == GLFW_KEY_LEFT) player->left(player);
		if (key == GLFW_KEY_RIGHT) player->right(player);
		if (key == GLFW_KEY_UP) player->forward(player);
		if (key == GLFW_KEY_DOWN) player->back(player);
		if (key == GLFW_KEY_SPACE) scene->printObjectID(player);
	}
	if (action == GLFW_RELEASE) {
		
		if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT)player->turnStop();

		if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) player->moveStop();
	}
}


void initOpenGLProgram(GLFWwindow* window) {
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window,keyCallback);
	
	sp = new ShaderProgram("v_shader.glsl", NULL, "f_shader.glsl");
	scene = new Scene("Gallery");
	scene->loadLevel();
	player = new Player();
}


void freeOpenGLProgram(GLFWwindow* window) {
	scene->clean();
	delete player;
	delete scene;
	delete sp;
}


void drawScene(GLFWwindow* window) {
	sp->use();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V = glm::lookAt(player->cam->position, player->cam->position + player->cam->dir, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 0.1f, 50.0f);
	
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
	glUniform4fv(sp->u("lp1"), 1, glm::value_ptr(glm::vec4(0, 13.5, -10, 1)));
	glUniform4fv(sp->u("lp2"), 1, glm::value_ptr(glm::vec4(0, 13.5, 20, 1)));
	
	glUniform4fv(sp->u("viewerPosition"), 1, glm::value_ptr(glm::vec4(player->pos, 1.0f)));
	scene->draw(sp);

	glfwSwapBuffers(window);
}

int main(void)
{
	srand(time(NULL));
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "Can't initialize GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1920,1080, "OpenGL", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	GLenum err;
	if ((err=glewInit()) != GLEW_OK) {
		fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window);

	glfwSetTime(0);

	while (!glfwWindowShouldClose(window))
	{		
		player->update(glfwGetTime());
		glfwSetTime(0);
		drawScene(window);
		glfwPollEvents();
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
