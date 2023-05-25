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
	Texcoord = uv;
	gl_Position = proj * view * model * vec4(position, 1.0);
}

