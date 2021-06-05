#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <shader_loader/shader_loader.hpp>


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


void glew_init(){
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW.\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}
}


int main(){
	GLFWwindow* window = glfw_init();
	glew_init();

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint programID = load_shaders("shader/vertex.glsl", "shader/fragment.glsl");

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	GLuint vertex_buffer_id;
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	do {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0
	);

	glDeleteBuffers(1, &vertex_buffer_id);
	glDeleteVertexArrays(1, &vertex_array_id);
	glDeleteProgram(programID);

	glfwTerminate();

	return 0;
}

