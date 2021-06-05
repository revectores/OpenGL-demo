cmake_minimum_required (VERSION 3.0)
project (opengl-demos)
find_package(OpenGL REQUIRED)


add_subdirectory(
	include
)


include_directories (
	include/glew/include/
	include/glfw/include/
	include/glm/
	.
)


set (ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_220
)


add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
)


add_executable(opengl_window
	opengl_window/opengl_window.cpp
)
target_link_libraries(opengl_window ${ALL_LIBS})
set_target_properties(opengl_window PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "opengl_window"
	LIBRARY_OUTPUT_DIRECTORY "opengl_window"
	RUNTIME_OUTPUT_DIRECTORY "opengl_window"
)

