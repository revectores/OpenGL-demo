#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils.hpp"
#include "shader_loader.hpp"
#include "texture_loader.hpp"
#include "obj_loader.hpp"
#include "events.hpp"


int main(){
	GLFWwindow* window = glfw_init();
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwPollEvents();
	glfwSetCursorPos(window, 1024/2, 768/2);

	glew_init();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	std::vector<face_t> faces = load_obj("cube.obj");
	auto face_vector_triple = extract_face_components(faces);
	auto vertices = std::get<VERTEX>(face_vector_triple);
	auto textures = std::get<TEXTURE>(face_vector_triple);
	auto normals  = std::get<NORMAL>(face_vector_triple);

	GLuint vertex_array_id  = create_vertex_array();
	GLuint vertex_buffer_id = create_buffer((const GLfloat*)&vertices[0], vertices.size() * sizeof(glm::vec3));
	GLuint uv_buffer_id     = create_buffer((const GLfloat*)&textures[0], textures.size() * sizeof(glm::vec2));
	GLuint program_id = load_shaders("shader/vertex.glsl", "shader/fragment.glsl");
	GLuint texture = load_dds("uvmap.DDS");
	GLuint texture_id = glGetUniformLocation(program_id, "texture_sampler");
	GLuint matrix_id  = glGetUniformLocation(program_id, "mvp");

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	while (!is_closed(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program_id);

		compute_matrices_from_inputs(window);
		glm::mat4 projection = get_projection_matrix();
		glm::mat4 view       = get_view_matrix();
		glm::mat4 model      = glm::mat4(1.0);
		glm::mat4 mvp        = projection * view * model;
		glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(texture_id, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_id);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vertex_buffer_id);
	glDeleteBuffers(1, &uv_buffer_id);
	glDeleteVertexArrays(1, &vertex_array_id);
	glDeleteVertexArrays(1, &texture_id);
	glDeleteProgram(program_id);
	glfwTerminate();
	return 0;
}
