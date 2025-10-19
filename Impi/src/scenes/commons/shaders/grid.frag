#version 330 core
out vec4 outColor;

in vec3 near;
in vec3 far;

void main() {
    float t = -near.y / (far.y-near.y); // Camera-ray
    outColor = vec4(1.0, 0.0, 0.0, 0.0);
}