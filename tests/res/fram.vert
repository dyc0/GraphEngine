#version 150 core

in vec3 position;
in vec2 uv;
in vec3 normal;

out vec2 Texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	mat3 scale_f = mat3(0.7);
	mat4 scale = mat4(scale_f);
	Texcoord = uv;
	gl_Position = proj * view * model * scale * vec4(position, 1.0);
}

