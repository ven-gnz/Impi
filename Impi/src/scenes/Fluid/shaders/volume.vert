#version 430 core

layout(std140, binding = 0) uniform ViewUniforms
{   mat4 view;
    mat4 projection;
    vec3 cameraPos;
    float padding;
};

layout(location = 0)in vec3 aPos;
layout(location = 1)in vec3 aNorm;
layout(location = 2)in vec2 aTex;


uniform mat4 model;

uniform vec3 color;
out vec3 fragColor;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   fragColor = color;
}