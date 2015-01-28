#version 150
// shader for wave visualization in left panel

// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec2 texcoord;

// the time value is passed into the shader by the OF app.
uniform vec2 scale;
uniform float updatePosition;

// this is how we receive the texture
uniform sampler2DRect tex0;

out vec2 texCoordVarying;

out vec4 vPos;

void main()
{
  // get the position of the vertex relative to the modelViewProjectionMatrix
  vec4 modifiedPosition = modelViewProjectionMatrix * position;
  
  // we need to scale up the values we get from the texture
  // float scale = 200;
  
  // here we get the red channel value from the texture
  // to use it as vertical displacement
  float displacementY = texture(tex0, texcoord).r;
  
  // use the displacement we created from the texture data
  // to modify the vertex position
  // use old_scale if x > updatePosition
  modifiedPosition.y += (displacementY * scale[0] - scale[0]/2) * step(updatePosition, texcoord.x);
  // use new_scale if x < update position
  modifiedPosition.y += (displacementY * scale[1] - scale[1]/2) * (1-step(updatePosition, texcoord.x));
	
  // this is the resulting vertex position
  gl_Position = modifiedPosition;
  
  // pass the texture coordinates to the fragment shader
  texCoordVarying = texcoord;
  
  vPos = position;
}