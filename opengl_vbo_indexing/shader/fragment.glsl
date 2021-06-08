#version 330 core

in vec2 uv;
in vec3 position_worldspace;
in vec3 normal_cameraspace;
in vec3 eye_direction_cameraspace;
in vec3 light_direction_cameraspace;

out vec3 color;

uniform sampler2D texture_sampler;
uniform mat4 mv;
uniform vec3 light_position_worldspace;

void main(){
	vec3  light_color = vec3(1, 1, 1);
	float light_power = 50.0f;

	vec3 material_diffuse_color  = texture(texture_sampler, uv).rgb;
	vec3 material_ambient_color  = vec3(0.1, 0.1, 0.1) * material_diffuse_color;
	vec3 material_specular_color = vec3(0.3, 0.3, 0.3);

	float distance = length(light_position_worldspace - position_worldspace);

	vec3 n = normalize(normal_cameraspace);
	vec3 l = normalize(light_direction_cameraspace);
	float cos_theta = clamp(dot(n, l), 0, 1);

	vec3 e = normalize(eye_direction_cameraspace);
	vec3 r = reflect(-l,n);
	float cos_alpha = clamp(dot(e, r), 0, 1);

	color = material_ambient_color
	      + material_diffuse_color  * light_color * light_power * cos_theta / (distance * distance)
	      + material_specular_color * light_color * light_power * pow(cos_alpha, 5) / (distance * distance);
}