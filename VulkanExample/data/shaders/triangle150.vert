#version 150


uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

in vec3 inPos;
in vec3 inColor;

out vec3 outColor;

void main() 
{
	outColor = inColor;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPos.xyz, 1.0);
}
