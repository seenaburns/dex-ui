#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;

void main(void)
{
	gl_Position = position;
}