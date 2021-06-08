#version 330 core

layout(location = 0) in vec3 vertex_position_modelspace;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 vertex_normal_modelspace;

out vec2 uv;
out vec3 position_worldspace;
out vec3 normal_cameraspace;
out vec3 eye_direction_cameraspace;
out vec3 light_direction_cameraspace;

uniform mat4 mvp;
uniform mat4 v;
uniform mat4 m;
uniform vec3 light_position_worldspace;

void main(){
	gl_Position =  mvp * vec4(vertex_position_modelspace, 1);
	position_worldspace = (m * vec4(vertex_position_modelspace, 1)).xyz;
	vec3 vertex_position_cameraspace = (v * m * vec4(vertex_position_modelspace,1)).xyz;
	eye_direction_cameraspace = vec3(0, 0, 0) - vertex_position_cameraspace;

	vec3 light_position_cameraspace = (v * vec4(light_position_worldspace, 1)).xyz;
	light_direction_cameraspace = light_position_cameraspace + eye_direction_cameraspace;
	normal_cameraspace = (v * m * vec4(vertex_normal_modelspace, 0)).xyz;
	uv = vertex_uv;
}
