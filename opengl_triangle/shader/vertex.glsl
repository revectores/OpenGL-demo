#version 330 core

layout(location = 0) in vec3 vertex_position_modelspace;

void main(){
    gl_Position.xyz = vertex_position_modelspace;
    gl_Position.w = 1.0;
}
