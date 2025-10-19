#version 330 core
uniform mat4 view;
uniform mat4 projection;


vec3 gridPlane[6] = vec3[](
    vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);



void main() {
    vec4 worldPos = vec4(gridPlane[gl_VertexID], 1.0);
    gl_Position = projection * view * worldPos;
}