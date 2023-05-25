#version 150 core

in vec3 position;
in vec3 normal;
in vec2 uv;

out vec3 Color;
out vec2 UV;

void main()
{
	Color = normal;
	UV = uv;
	gl_Position = vec4(position, 1.0);
}
