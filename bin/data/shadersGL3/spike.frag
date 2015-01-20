#version 150

uniform vec4 globalColor;
uniform float abspos;
uniform float size;

out vec4 outputColor;

void main()
{
  float r = globalColor[0];
  float g = globalColor[1];
  float b = globalColor[2];
  float a = 1.0;
  a -= (1-smoothstep(abspos, abspos+5, gl_FragCoord.x));
  a -= smoothstep(abspos+size-5, abspos+size, gl_FragCoord.x);
  outputColor = vec4(r,g,b,a);
}