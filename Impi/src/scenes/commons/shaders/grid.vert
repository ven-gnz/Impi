#version 330 core

out vec3 WorldPos;

layout(std140) uniform viewUnis
{   mat4 view;
    mat4 projection;
    vec3 cameraPos;
    float padding;
};

const vec3 Pos[4] = vec3[4]
( vec3(-1.0, 0.0, -1.0),
  vec3(1.0, 0.0, -1.0),
  vec3(1.0, 0.0, 1.0),
  vec3(-1.0, 0.0, 1.0)
);

const int Indices[6] = int[6](0,2,1,2,0,3);

void main()
{
    int Index = Indices[gl_VertexID];


    vec3 vPos_init = Pos[Index];

    //vPos_init.x += cameraPos.x;
    //vPos_init.z += cameraPos.z;

    vec4 vPos4 = vec4(vPos_init, 1.0);

    gl_Position = projection * view * vPos4;

    WorldPos = vPos_init;
}