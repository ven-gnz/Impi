#version 420 core

out vec4 fc;
in vec3 vColor;


void main()
{
    fc = vec4(vColor, 1.0);
}