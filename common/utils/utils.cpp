#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include "utils.hpp"


GLFWwindow* glfw_init(){
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		exit(-1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "Demo 1", NULL, NULL);

	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	return window;
}


bool is_closed(GLFWwindow* window){
	return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window) != 0;
}


void glew_init(){
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW.\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}
}


GLuint create_vertex_array(){
	GLuint vertex_array_id;

	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	return vertex_array_id;
}


GLuint create_buffer(const void* buffer_data, int buffer_data_size){
	GLuint buffer_id;

	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, buffer_data_size, buffer_data, GL_STATIC_DRAW);

	return buffer_id;
}
