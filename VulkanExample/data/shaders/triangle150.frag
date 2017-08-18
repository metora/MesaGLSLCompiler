#version 150

in vec3 inColor;

out vec4 outFragColor;

void main() 
{
    outFragColor = vec4(inColor, 1.0);
}