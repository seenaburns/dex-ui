#version 150

out vec4 outputColor;

void main()
{
	float r = 0.0;
	float g = 0.0;
	float b = 0.0;
	float a = 0.3 * step(2, mod(gl_FragCoord.y+1, 3));
	outputColor = vec4(r, g, b, a);
}