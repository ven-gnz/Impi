#version 330 core


in vec3 near;
in vec3 far;

out vec4 outColor;

void main() {

   //outColor = vec4(normalize(abs(near)), 1.0);
   //float t = -near.y / (far.y - near.y);
   //float opacity = 1.0 * float(t > 0);
   outColor = vec4(1.0, 0.0, 0.0, 1.0);
}