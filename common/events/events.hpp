#ifndef EVENTS_HPP
#define EVENTS_HPP
#include <GLFW/glfw3.h>

void compute_matrices_from_inputs(GLFWwindow* window);
glm::mat4 get_view_matrix();
glm::mat4 get_projection_matrix();

#endif