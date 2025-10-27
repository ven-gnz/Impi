#version 420 core

layout(std140, binding = 0) uniform ViewUniforms
{   mat4 view;
    mat4 projection;
    vec3 cameraPos;
    float padding;
};

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 fCol;

out vec3 fragColor;


void main()
{
    fragColor = fCol;
    gl_Position = projection * view * vec4(aPos, 1.0);

}