#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 color = vec3(0.9, 0.9, 0.9);
uniform vec3 lightDir = normalize(vec3(0.0, 5.0, 0.0));

void main() {
    float diff = max(dot(normalize(Normal), -lightDir), 0.0);
    vec3 lighting = (0.1 + 0.9 * diff) * color;
    FragColor = vec4(lighting, 1.0);
}