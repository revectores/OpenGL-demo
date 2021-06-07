#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <vector>
#include <tuple>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "obj_loader.hpp"


const char* type_notations[OBJ_LINE_TYPE_N] = {"v", "vt", "vn", "f"};
const int   type_param_sizes[OBJ_LINE_TYPE_N] = {VERTEX_PARAM_SIZE, TEXTURE_PRRAM_SIZE, NORMAL_PARAM_SIZE, FACE_PARAM_SIZE};


size_t tokenize(char *str, char **tokens){
	char *token;
	int token_cnt = 0;

	tokens[token_cnt++] = strtok(str, " ");
	while ((token = strtok(NULL, " "))){
		tokens[token_cnt++] = token;
	}

	tokens[token_cnt] = NULL;
	return token_cnt;
}



int find_index(char *input, char **targets, const size_t target_size){
	for (size_t index = 0; index < target_size; index++) {
		if (strcmp(input, targets[index]) == 0) return index;
	}
	return -1;
}


void panic(const char *err_msg){
	fprintf(stderr, "%s", err_msg);
	exit(-1);
}


raw_face_element_t read_face(char *raw_face_element_str){
	// printf("raw_face_element_str: %s\n", raw_face_element_str);
	char *c = raw_face_element_str;
	raw_face_element_t raw_face_element;
	size_t index_field_offset = 0;

	while (*c && *c != '\n' && *c != '\r') {
		size_t index = 0;
		while (*c && *c != '/' && *c != '\n' && *c != '\r') {
			index *= 10;
			index += *c - '0';
			c++;
		}
		*(size_t*)((char*)(&raw_face_element) + index_field_offset) = index;
		index_field_offset += sizeof(size_t);
		if (*c == '/') c++;
	}

	// printf("raw face index: %zu %zu %zu\n", raw_face_element.vertex_index, raw_face_element.texture_index, raw_face_element.normal_index);

	assert(index_field_offset <= 3 * sizeof(size_t));
	return raw_face_element;
}


std::vector<face_t> load_obj(const char *obj_file_path){
	FILE *obj_file = fopen(obj_file_path, "r");
	if (!obj_file) panic("File does not exist");

	char obj_line_buffer[OBJ_LINE_BUFFER_SIZE];

	std::vector<glm::vec3>  vertices;
	std::vector<glm::vec2>  textures;
	std::vector<glm::vec3>  normals;
	std::vector<raw_face_t> raw_faces;

	char* tokens[MAX_TOKEN_SIZE];

	while ((fgets(obj_line_buffer, OBJ_LINE_BUFFER_SIZE, obj_file))){
		size_t token_size = tokenize(obj_line_buffer, tokens);
		size_t param_size = token_size - 1;

		if (token_size == 0) panic("Empty line get tokenized");
		int line_type = find_index(tokens[0], (char**)type_notations, OBJ_LINE_TYPE_N);
		if (line_type == -1) continue;
		if (param_size != type_param_sizes[line_type]) panic("Parameter numbers not fit");

		// printf("line_type  = %s\n", type_notations[line_type]);
		// printf("param_size = %lu\n", param_size);
		// for (size_t i = 0; i < token_size; i++){
		// 	printf("%s ", tokens[i]);
		// }
		// printf("\n");

		switch (line_type) {
		case VERTEX:
			vertices.push_back(glm::vec3(strtod(tokens[1], NULL), strtod(tokens[2], NULL), strtod(tokens[3], NULL)));
			break;

		case TEXTURE:
			textures.push_back(glm::vec2(strtod(tokens[1], NULL), strtod(tokens[2], NULL)));
			break;

		case NORMAL:
			normals.push_back(glm::vec3(strtod(tokens[1], NULL), strtod(tokens[2], NULL), strtod(tokens[3], NULL)));
			break;

		case FACE:
			raw_faces.push_back(raw_face_t {read_face(tokens[1]), read_face(tokens[2]), read_face(tokens[3])});
			break;
		}
	}

	std::vector<face_t> faces(raw_faces.size(), std::vector<face_element_t>(3));
	size_t face_cnt = 0;

	for (auto raw_face: raw_faces){
		size_t face_element_cnt = 0;
		for (auto raw_face_element: raw_face) {
			auto& face_element = faces[face_cnt][face_element_cnt];
			face_element.vertex  = vertices[raw_face_element.vertex_index - 1];
			face_element.texture = textures[raw_face_element.texture_index - 1];
			face_element.normal  = normals[raw_face_element.normal_index - 1];
			face_element_cnt++;
		}
		face_cnt++;
	}

	return faces;
}


face_vector_triple_t extract_face_components(std::vector<face_t> faces){
	face_vector_triple_t face_vector_triple(
		std::vector<glm::vec3>(FACE_PARAM_SIZE * faces.size()),
		std::vector<glm::vec2>(FACE_PARAM_SIZE * faces.size()),
		std::vector<glm::vec3>(FACE_PARAM_SIZE * faces.size())
	);

	size_t cnt = 0;

	for (auto face: faces) {
		for (auto face_element: face) {
			std::get<VERTEX> (face_vector_triple)[cnt]   = face_element.vertex;
			std::get<TEXTURE>(face_vector_triple)[cnt]   = face_element.texture;
			std::get<NORMAL> (face_vector_triple)[cnt++] = face_element.normal;
		}
	}

	return face_vector_triple;
}

// int main(){
// 	std::vector<face_t> faces = load_obj("cube.obj");
// 	for (auto face: faces) {
// 		for (auto face_element: face) {
// 			std::cout << glm::to_string(face_element.vertex) << std::endl;
// 			std::cout << glm::to_string(face_element.texture) << std::endl;
// 			std::cout << glm::to_string(face_element.normal) << std::endl;
// 			std::cout << std::endl;
// 		}
// 		std::cout << std::endl;
// 		std::cout << std::endl;
// 		std::cout << std::endl;
// 	}
// 	return 0;
// }
