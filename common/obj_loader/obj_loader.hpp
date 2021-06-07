#include <glm/glm.hpp>


typedef struct {
	size_t vertex_index;
	size_t texture_index;
	size_t normal_index;
} raw_face_element_t;

typedef std::vector<raw_face_element_t> raw_face_t;

typedef struct {
	glm::vec3 vertex;
	glm::vec2 texture;
	glm::vec3 normal;
} face_element_t;

typedef std::vector<face_element_t> face_t;


const size_t OBJ_LINE_BUFFER_SIZE = 1000;
const size_t VERTEX_PARAM_SIZE  = 3;
const size_t TEXTURE_PRRAM_SIZE = 2;
const size_t NORMAL_PARAM_SIZE  = 3;

// This loader only supports 3 vertices per face for now.
const size_t FACE_PARAM_SIZE    = 3;
const size_t MAX_PARAM_SIZE     = 4;
const size_t MAX_TOKEN_SIZE     = MAX_PARAM_SIZE + sizeof(char*) + sizeof(char*);
const size_t OBJ_LINE_TYPE_N    = 4;


enum obj_line_type {
	VERTEX,
	TEXTURE,
	NORMAL,
	FACE
};

std::vector<face_t> load_obj(const char* obj_file_path);
