#version 420 core


layout(std140, binding = 0) uniform ViewUniforms
{   mat4 view;
    mat4 projection;
    vec3 cameraPos;
    float padding;
};

uniform mat4 model;

layout(location = 0)in vec3 aPos;
layout(location = 1)in vec3 aNorm;
layout(location = 2)in vec2 aTex;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}