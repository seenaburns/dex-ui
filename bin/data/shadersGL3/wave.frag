#version 150

uniform sampler2DRect tex0;
uniform float alpha_adjust;

in vec2 texCoordVarying;

out vec4 outputColor;

in vec4 vPos;

void main()
{
    // gl_FragCoord contains the window relative coordinate for the fragment.
    // we use gl_FragCoord.x position to control the red color value.
    // we use gl_FragCoord.y position to control the green color value.
    // please note that all r, g, b, a values are between 0 and 1.
    
    float windowWidth = 800;
    float windowHeight = 800.0;
  
  float r = 0.32;
  float g = 0.41;
  float b = 0.36;
//	float r = gl_FragCoord.x / windowWidth;
//	float g = 1.0;
//	float b = gl_FragCoord.y / windowHeight;
//  float b = texture(tex0, texCoordVarying)[0]*texture(tex0, texCoordVarying)[0];
//	float a = texture(tex0, texCoordVarying)[0]*alpha_adjust;
  float ax = (200-abs(vPos.x))/200+0.4;
  float ay = (200-abs(vPos.y))/200+0.4;
//  float a = clamp(ax*ay,0,1);
  float a = clamp(ax*ay,0,1)*(texture(tex0, texCoordVarying)[0])*alpha_adjust;
//  a += min(sign(gl_FragCoord.y-300),0);
//  a += min(-1*sign(gl_FragCoord.y-500),0);
//  a = clamp(a,0,1);
//	outputColor = vec4(r, g, b, a);
  outputColor = vec4(r,g,b,a);// texture(tex0, texCoordVarying)[0]);
}