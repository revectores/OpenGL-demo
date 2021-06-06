#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader_loader/shader_loader.hpp"


const GLfloat vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 0.0f,  1.0f, 0.0f,
};

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
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
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


GLuint create_buffer(const GLfloat* buffer_data, int buffer_data_size){
	GLuint buffer_id;

	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, buffer_data_size, buffer_data, GL_STATIC_DRAW);

	return buffer_id;
}


int main(){
	GLFWwindow* window = glfw_init();
	glew_init();
	GLuint program_id = load_shaders("shader/vertex.glsl", "shader/fragment.glsl");
	GLuint vertex_array_id  = create_vertex_array();
	GLuint vertex_buffer_id = create_buffer(vertex_buffer_data, sizeof(vertex_buffer_data));

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	while (!is_closed(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program_id);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vertex_buffer_id);
	glDeleteVertexArrays(1, &vertex_array_id);
	glDeleteProgram(program_id);
	glfwTerminate();
	return 0;
}
