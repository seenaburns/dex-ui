#version 150

uniform sampler2DRect tex0;
//in vec2 texCoordVarying;
out vec4 outputColor;
in vec4 vert_position;

void main()
{
  vec4 texout = texture(tex0, vec2(vert_position.x,vert_position.y));
  float r = 0.32;
  float g = 0.41;
  float b = 0.36;
  // Bound display between start and end x positions
	float a = texout[0]*1.2;
	outputColor = vec4(r,g,b,a);
}