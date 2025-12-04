#version 430
in vec2 uv;
out vec4 FragColor;
uniform sampler2D fluidTexture;
void main() {
    FragColor = texture(fluidTexture, uv);
}