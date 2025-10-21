#version 330 core

layout(std140) uniform viewUnis
{
    mat4 view;
    mat4 projection;
    vec3 cameraPos;
    float padding;
};

out vec3 near;
out vec3 far;

vec3 gridPlane[6] = vec3[](
    vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);

vec3 UnprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main() {
    vec3 p = gridPlane[gl_VertexID].xyz;
    near = UnprojectPoint(p.x, p.y, 0.0, projection, view).xyz;
    far  = UnprojectPoint(p.x, p.y, 1.0, projection, view).xyz;
    gl_Position = vec4(p,1.0);
    

}