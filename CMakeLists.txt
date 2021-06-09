cmake_minimum_required (VERSION 3.0)
project (opengl-demos)
set (CMAKE_CXX_STANDARD 20)
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

include_directories (
	${CMAKE_SOURCE_DIR}/common/utils
	${CMAKE_SOURCE_DIR}/common/shader_loader
	${CMAKE_SOURCE_DIR}/common/texture_loader
	${CMAKE_SOURCE_DIR}/common/vbo_indexer
	${CMAKE_SOURCE_DIR}/common/obj_loader
	${CMAKE_SOURCE_DIR}/common/events
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
	common/utils/utils.hpp
	common/utils/utils.cpp
	common/shader_loader/shader_loader.hpp
	common/shader_loader/shader_loader.cpp

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
	common/utils/utils.hpp
	common/utils/utils.cpp
	common/shader_loader/shader_loader.hpp
	common/shader_loader/shader_loader.cpp

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
	common/utils/utils.hpp
	common/utils/utils.cpp
	common/shader_loader/shader_loader.hpp
	common/shader_loader/shader_loader.cpp

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
	common/utils/utils.hpp
	common/utils/utils.cpp
	common/shader_loader/shader_loader.hpp
	common/shader_loader/shader_loader.cpp
	common/texture_loader/texture_loader.hpp
	common/texture_loader/texture_loader.cpp

	opengl_textured_cube/shader/vertex.glsl
	opengl_textured_cube/shader/fragment.glsl
)
target_link_libraries(opengl_textured_cube ${ALL_LIBS})
set_target_properties(opengl_textured_cube PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "opengl_textured_cube"
	LIBRARY_OUTPUT_DIRECTORY "opengl_textured_cube"
	RUNTIME_OUTPUT_DIRECTORY "opengl_textured_cube"
)


add_executable(opengl_event
	opengl_event/opengl_event.cpp
	common/utils/utils.hpp
	common/utils/utils.cpp
	common/shader_loader/shader_loader.hpp
	common/shader_loader/shader_loader.cpp
	common/texture_loader/texture_loader.hpp
	common/texture_loader/texture_loader.cpp
	common/events/events.hpp
	common/events/events.cpp

	opengl_event/shader/vertex.glsl
	opengl_event/shader/fragment.glsl
)
target_link_libraries(opengl_event ${ALL_LIBS})
set_target_properties(opengl_event PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "opengl_event"
	LIBRARY_OUTPUT_DIRECTORY "opengl_event"
	RUNTIME_OUTPUT_DIRECTORY "opengl_event"
)



add_executable(opengl_model_loading
	opengl_model_loading/opengl_model_loading.cpp
	common/utils/utils.hpp
	common/utils/utils.cpp
	common/shader_loader/shader_loader.hpp
	common/shader_loader/shader_loader.cpp
	common/texture_loader/texture_loader.hpp
	common/texture_loader/texture_loader.cpp
	common/obj_loader/obj_loader.hpp
	common/obj_loader/obj_loader.cpp
	common/events/events.hpp
	common/events/events.cpp

	opengl_model_loading/shader/vertex.glsl
	opengl_model_loading/shader/fragment.glsl
)
target_link_libraries(opengl_model_loading ${ALL_LIBS})
set_target_properties(opengl_model_loading PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "opengl_model_loading"
	LIBRARY_OUTPUT_DIRECTORY "opengl_model_loading"
	RUNTIME_OUTPUT_DIRECTORY "opengl_model_loading"
)


add_executable(opengl_shading
	opengl_shading/opengl_shading.cpp
	common/utils/utils.hpp
	common/utils/utils.cpp
	common/shader_loader/shader_loader.hpp
	common/shader_loader/shader_loader.cpp
	common/texture_loader/texture_loader.hpp
	common/texture_loader/texture_loader.cpp
	common/obj_loader/obj_loader.hpp
	common/obj_loader/obj_loader.cpp
	common/events/events.hpp
	common/events/events.cpp

	opengl_shading/shader/vertex.glsl
	opengl_shading/shader/fragment.glsl
)
target_link_libraries(opengl_shading ${ALL_LIBS})
set_target_properties(opengl_shading PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "opengl_shading"
	LIBRARY_OUTPUT_DIRECTORY "opengl_shading"
	RUNTIME_OUTPUT_DIRECTORY "opengl_shading"
)


add_executable(opengl_vbo_indexing
	opengl_vbo_indexing/opengl_vbo_indexing.cpp
	common/utils/utils.hpp
	common/utils/utils.cpp
	common/shader_loader/shader_loader.hpp
	common/shader_loader/shader_loader.cpp
	common/texture_loader/texture_loader.hpp
	common/texture_loader/texture_loader.cpp
	common/obj_loader/obj_loader.hpp
	common/obj_loader/obj_loader.cpp
	common/vbo_indexer/vbo_indexer.hpp
	common/vbo_indexer/vbo_indexer.cpp
	common/events/events.hpp
	common/events/events.cpp

	opengl_vbo_indexing/shader/vertex.glsl
	opengl_vbo_indexing/shader/fragment.glsl
)
target_link_libraries(opengl_vbo_indexing ${ALL_LIBS})
set_target_properties(opengl_vbo_indexing PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "opengl_vbo_indexing"
	LIBRARY_OUTPUT_DIRECTORY "opengl_vbo_indexing"
	RUNTIME_OUTPUT_DIRECTORY "opengl_vbo_indexing"
)



add_executable(opengl_transparency
	opengl_transparency/opengl_transparency.cpp
	common/utils/utils.hpp
	common/utils/utils.cpp
	common/shader_loader/shader_loader.hpp
	common/shader_loader/shader_loader.cpp
	common/texture_loader/texture_loader.hpp
	common/texture_loader/texture_loader.cpp
	common/obj_loader/obj_loader.hpp
	common/obj_loader/obj_loader.cpp
	common/vbo_indexer/vbo_indexer.hpp
	common/vbo_indexer/vbo_indexer.cpp
	common/events/events.hpp
	common/events/events.cpp

	opengl_transparency/shader/vertex.glsl
	opengl_transparency/shader/fragment.glsl
)
target_link_libraries(opengl_transparency ${ALL_LIBS})
set_target_properties(opengl_transparency PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "opengl_transparency"
	LIBRARY_OUTPUT_DIRECTORY "opengl_transparency"
	RUNTIME_OUTPUT_DIRECTORY "opengl_transparency"
)
