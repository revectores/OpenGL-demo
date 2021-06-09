#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* glfw_init();
bool is_closed(GLFWwindow* window);
void glew_init();
GLuint create_vertex_array();
GLuint create_buffer(const void* buffer_data, int buffer_data_size);
