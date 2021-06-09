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
	glEnable(GL_CULL_FACE);

	std::vector<face_t> faces = load_obj("suzanne.obj");
	auto face_vector_triple = extract_face_components(faces);
	auto vertices = std::get<VERTEX>(face_vector_triple);
	auto uvs      = std::get<TEXTURE>(face_vector_triple);
	auto normals  = std::get<NORMAL>(face_vector_triple);

	GLuint vertex_array  = create_vertex_array();
	GLuint vertex_buffer = create_buffer((const GLfloat*)&vertices[0], vertices.size() * sizeof(glm::vec3));
	GLuint uv_buffer     = create_buffer((const GLfloat*)&uvs[0],      uvs.size()      * sizeof(glm::vec2));
	GLuint normal_buffer = create_buffer((const GLfloat*)&normals[0],  normals.size()  * sizeof(glm::vec3));
	GLuint program       = load_shaders("shader/vertex.glsl", "shader/fragment.glsl");
	GLuint texture       = load_dds("uvmap.DDS");

	GLuint mvp_ul     = glGetUniformLocation(program, "mvp");
	GLuint model_ul   = glGetUniformLocation(program, "m");
	GLuint view_ul    = glGetUniformLocation(program, "v");
	GLuint light_ul   = glGetUniformLocation(program, "light_position_worldspace");
	GLuint texture_ul = glGetUniformLocation(program, "texture_sampler");

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	while (!is_closed(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);

		compute_matrices_from_inputs(window);
		glm::mat4 projection = get_projection_matrix();
		glm::mat4 view       = get_view_matrix();
		glm::mat4 model      = glm::mat4(1.0);
		glm::mat4 mvp        = projection * view * model;
		glUniformMatrix4fv(mvp_ul,   1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(model_ul, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(view_ul,  1, GL_FALSE, &view[0][0]);

		glm::vec3 light_pos = glm::vec3(4, 4, 4);
		glUniform3f(light_ul, light_pos.x, light_pos.y, light_pos.z);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(texture_ul, 0);


		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &uv_buffer);
	glDeleteBuffers(1, &normal_buffer);
	glDeleteProgram(program);
	glDeleteTextures(1, &texture);
	glDeleteVertexArrays(1, &vertex_array);
	glfwTerminate();
	return 0;
}
