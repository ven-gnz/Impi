#version 330 core


layout(location = 0) in vec2 aPos;

uniform mat4 view;
uniform mat4 projection;

out vec3 near;
out vec3 far;

vec3 deProject(float x, float y, float z) {
    mat4 invProj = inverse(projection);
    mat4 invView = inverse(view);
    vec4 clip = vec4(x, y, z, 1.0);
    vec4 eye = invProj * clip;
    eye /= eye.w;
    vec4 world = invView * eye;
    return world.xyz;
}

void main() {

    near = deProject(aPos.x, aPos.y, 0.0);
    far  = deProject(aPos.x, aPos.y, 1.0);
    gl_Position = projection * view * vec4(aPos, 0.0, 1.0);

}