#version 330 core
uniform mat4 view;
uniform mat4 projection;

out vec3 near;
out vec3 far;



vec3 gridPlane[6] = vec3[](
    vec3(1, 1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(-1, -1, 0), vec3(1, 1, 0), vec3(1, -1, 0)
);

vec3 deProject(float x, float y, float z, mat4 view, mat4 projection)
{
    vec4 worldPos = inverse(projection*view) * vec4(x,y,z,1.0);
    return worldPos.xyz / worldPos.w;

}



void main() {

    vec3 p = gridPlane[gl_VertexID].xyz;
    near = deProject(p.x, p.y, 0.0, view, projection).xyz;
    far = deProject(p.x, p.y, 1.0, view, projection).xyz;
    gl_Position = vec4(p.xy, 0.0, 1.0);
}