#version 430
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTex;

layout(std140, binding = 0) uniform ViewUniforms {
    mat4 view;
    mat4 projection;
    vec3 cameraPos;
    float padding;
};

out vec2 uv;
void main() {
    uv = aTex;
    gl_Position = vec4(aPos, 0.0, 1.0);
}