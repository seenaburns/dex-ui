#version 150

uniform vec4 globalColor;
uniform float minTheta;
uniform float maxTheta;
uniform vec2 center;
uniform float alphaSub;

out vec4 outputColor;

void main()
{
  vec2 deltaCoord = vec2(gl_FragCoord.x, gl_FragCoord.y)-center;
  float angle = atan(deltaCoord.y, deltaCoord.x);
  angle = mod(angle+6.28-maxTheta,6.28);
  angle -= smoothstep(6,6.28,angle)*6.28;
  
//  vec3 brightC = vec3(95,141,110);
//  vec3 brightC = vec3(140,194,170); // 8CC2AA
  vec3 brightC = vec3(116,161,141); // 8CC2AA
//  vec3 darkC = vec3(13,16,14);
//  vec3 darkC = vec3(58,74,65);
  vec3 darkC = vec3(53,97,79);
  
  float a = angle/6.28;
  a = pow(a,3);
  a -= alphaSub;
  
  vec3 color = mix(darkC, brightC, a);
  float r = color[0]/255.0;
  float g = color[1]/255.0;
  float b = color[2]/255.0;
  //  float a = smoothstep(minTheta,maxTheta,angle);
  outputColor = vec4(r,g,b,a);
}