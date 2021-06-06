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



add_executable(opengl_triangle
	opengl_triangle/opengl_triangle.cpp
	utils/utils.hpp
	utils/utils.cpp
	shader_loader/shader_loader.hpp
	shader_loader/shader_loader.cpp

	opengl_triangle/shader/vertex.glsl
	opengl_triangle/shader/fragment.glsl
)
target_link_libraries(opengl_triangle ${ALL_LIBS})
set_target_properties(opengl_triangle PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "opengl_triangle"
	LIBRARY_OUTPUT_DIRECTORY "opengl_triangle"
	RUNTIME_OUTPUT_DIRECTORY "opengl_triangle"
)



add_executable(opengl_triangle_transform
	opengl_triangle_transform/opengl_triangle_transform.cpp
	utils/utils.hpp
	utils/utils.cpp
	shader_loader/shader_loader.hpp
	shader_loader/shader_loader.cpp

	opengl_triangle_transform/shader/vertex.glsl
	opengl_triangle_transform/shader/fragment.glsl
)
target_link_libraries(opengl_triangle_transform ${ALL_LIBS})
set_target_properties(opengl_triangle_transform PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "opengl_triangle_transform"
	LIBRARY_OUTPUT_DIRECTORY "opengl_triangle_transform"
	RUNTIME_OUTPUT_DIRECTORY "opengl_triangle_transform"
)



add_executable(opengl_colored_cube
	opengl_colored_cube/opengl_colored_cube.cpp
	utils/utils.hpp
	utils/utils.cpp
	shader_loader/shader_loader.hpp
	shader_loader/shader_loader.cpp

	opengl_colored_cube/shader/vertex.glsl
	opengl_colored_cube/shader/fragment.glsl
)
target_link_libraries(opengl_colored_cube ${ALL_LIBS})
set_target_properties(opengl_colored_cube PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "opengl_colored_cube"
	LIBRARY_OUTPUT_DIRECTORY "opengl_colored_cube"
	RUNTIME_OUTPUT_DIRECTORY "opengl_colored_cube"
)



add_executable(opengl_textured_cube
	opengl_textured_cube/opengl_textured_cube.cpp
	utils/utils.hpp
	utils/utils.cpp
	shader_loader/shader_loader.hpp
	shader_loader/shader_loader.cpp
	texture_loader/texture_loader.hpp
	texture_loader/texture_loader.cpp

	opengl_textured_cube/shader/vertex.glsl
	opengl_textured_cube/shader/fragment.glsl
)
target_link_libraries(opengl_textured_cube ${ALL_LIBS})
set_target_properties(opengl_textured_cube PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "opengl_textured_cube"
	LIBRARY_OUTPUT_DIRECTORY "opengl_textured_cube"
	RUNTIME_OUTPUT_DIRECTORY "opengl_textured_cube"
)
