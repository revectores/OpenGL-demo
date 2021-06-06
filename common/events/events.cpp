#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "events.hpp"


glm::mat4 view_matrix;
glm::mat4 projection_matrix;
glm::mat4 get_view_matrix(){
	return view_matrix;
}
glm::mat4 get_projection_matrix(){
	return projection_matrix;
}

glm::vec3 position = glm::vec3(0, 0, 5);
float horizontal_angle =  3.140f;
float vertical_angle   =  0.000f;
float initial_FoV      = 45.000f;
float speed            =  3.000f;
float mouse_speed      =  0.005f;


void compute_matrices_from_inputs(GLFWwindow* window){
	static double previous_time = glfwGetTime();
	double current_time = glfwGetTime();

	float time_delta = current_time - previous_time;
	double x, y;

	glfwGetCursorPos(window, &x, &y);
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	horizontal_angle += mouse_speed * (1024 / 2 - x);
	vertical_angle   += mouse_speed * ( 768 / 2 - y);

	glm::vec3 direction(
		cos(vertical_angle) * sin(horizontal_angle),
		sin(vertical_angle),
		cos(vertical_angle) * cos(horizontal_angle)
	);

	glm::vec3 right(
		sin(horizontal_angle - 3.14f / 2),
		0,
		cos(horizontal_angle - 3.14f / 2)
	);

	glm::vec3 up = glm::cross(right, direction);

	if (glfwGetKey(window, GLFW_KEY_UP)    == GLFW_PRESS) position += direction * time_delta * speed;
	if (glfwGetKey(window, GLFW_KEY_DOWN)  == GLFW_PRESS) position -= direction * time_delta * speed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) position += right * time_delta * speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_PRESS) position -= right * time_delta * speed;

	float FoV = initial_FoV;

	projection_matrix = glm::perspective(glm::radians(FoV), 4.0f / 3, 0.1f, 100.0f);
	view_matrix = glm::lookAt(position, position + direction, up);

	previous_time = current_time;
}