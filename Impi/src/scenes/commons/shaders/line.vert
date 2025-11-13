#version 420 core

layout(location = 0) in vec3 aPos;

layout(std140, binding = 0) uniform ViewUniforms
{   mat4 view;
    mat4 projection;
    vec3 cameraPos;
    float padding;
};


uniform vec3 uColor;

out vec3 vColor;

void main()
{
    gl_Position = projection*view*vec4(aPos, 1.0);
    vColor = uColor;
}