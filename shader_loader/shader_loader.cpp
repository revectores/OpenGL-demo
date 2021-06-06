#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include <GL/glew.h>
#include "shader_loader.hpp"


std::string read_file(const char* file_path) {
	std::ifstream ifs(file_path, std::ios::in);
	std::string content;
	std::stringstream sstr;
	sstr << ifs.rdbuf();
	content = sstr.str();
	ifs.close();
	return content;
}


void print_shader_log(GLuint shader_id){
	GLint res = GL_FALSE;
	GLint info_log_length;

	glGetShaderiv(shader_id, GL_COMPILE_STATUS,  &res);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if (info_log_length > 0) {
		GLchar* shader_info_log = (GLchar*) malloc(info_log_length + 1);
		glGetShaderInfoLog(shader_id, info_log_length, NULL, shader_info_log);
		printf("[SHADER INFO LOG] %s\n", shader_info_log);
		free(shader_info_log);
	}
}


void print_program_log(GLuint program_id){
	GLint res = GL_FALSE;
	GLint info_log_length;

	glGetProgramiv(program_id, GL_LINK_STATUS, &res);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if (info_log_length > 0) {
		GLchar* program_info_log = (GLchar*) malloc(info_log_length + 1);
		glGetProgramInfoLog(program_id, info_log_length, NULL, program_info_log);
		printf("[PROGRAM INFO LOG] %s\n", program_info_log);
		free(program_info_log);
	}
}


GLuint load_shader(const char* shader_file_path, GLenum shader_type){
	GLuint shader_id = glCreateShader(shader_type);
	std::string shader_code = read_file(shader_file_path);
	char const* shader_code_ptr = shader_code.c_str();

	glShaderSource(shader_id, 1, &shader_code_ptr, NULL);
	glCompileShader(shader_id);
	print_shader_log(shader_id);
	return shader_id;
}


GLuint load_shaders(const char* vertex_file_path, const char* fragment_file_path){
	GLuint program_id = glCreateProgram();

	GLuint vertex_shader_id   = load_shader(vertex_file_path,   GL_VERTEX_SHADER);
	GLuint fragment_shader_id = load_shader(fragment_file_path, GL_FRAGMENT_SHADER);
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);

	print_program_log(program_id);

	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return program_id;
}

