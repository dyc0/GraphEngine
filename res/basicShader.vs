#version 120

attribute vec3 position_;
attribute vec2 texCoord_;

varying vec2 texCoord0;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position_, 1.0);
    texCoord0 = texCoord_;
}
