#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/utils.hpp"
#include "shader_loader/shader_loader.hpp"


static const GLfloat vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 0.0f,  1.0f, 0.0f,
};


glm::mat4 make_mvp(){
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 mvp = projection * view * model;
	return mvp;
}


int main(){
	GLFWwindow* window = glfw_init();
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glew_init();

	GLuint program_id = load_shaders("shader/vertex.glsl", "shader/fragment.glsl");
	GLuint vertex_array_id = create_vertex_array();
	GLuint vertex_buffer_id = create_buffer(vertex_buffer_data, sizeof(vertex_buffer_data));
	GLuint matrix_id = glGetUniformLocation(program_id, "mvp");

	glm::mat4 mvp = make_mvp();
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	while (!is_closed(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program_id);

		glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);

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
