#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
out vec4 vert_position;
void main(){
	gl_Position = modelViewProjectionMatrix * position;
  vert_position = position;
}