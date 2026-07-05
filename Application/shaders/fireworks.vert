#version 420 core

layout(std140, binding = 0) uniform ViewUniforms
{   mat4 view;
    mat4 projection;
    vec3 cameraPos;
    float padding;
};

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec4 fCol;

out vec3 fragColor;


void main()
{
    fragColor = fCol.xyz;
    gl_PointSize = 5.0f;
    gl_Position = projection * view * aPos;

}