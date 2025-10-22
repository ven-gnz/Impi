#version 420 core



layout(std140, binding = 0) uniform ViewUniforms
{   mat4 view;
    mat4 projection;
    vec3 cameraPos;
    float padding;
};

out vec3 WorldPos;
out vec3 CamPos;
out float GridSize;



const vec3 Pos[4] = vec3[4]
( vec3(-1.0, 0.0, -1.0),
  vec3(1.0, 0.0, -1.0),
  vec3(1.0, 0.0, 1.0),
  vec3(-1.0, 0.0, 1.0)
);

const int Indices[6] = int[6](0,2,1,2,0,3);
const float gridSize = 100;

void main()
{

    int Index = Indices[gl_VertexID];

    vec3 vPos_init = Pos[Index] * gridSize;

    vPos_init.x += cameraPos.x;
    vPos_init.z += cameraPos.z;

    // without some y offset, the plane gets clipped. Took ~ 8 hours to find bug?

    // Now manually set to exactly halfway of default cameraPos. Will investigate further.
    vPos_init.y -= 0.5;

    vec4 vPos4 = vec4(vPos_init, 1.0);
    
    WorldPos = vPos_init;
    GridSize = gridSize;
    gl_Position = projection * view * vPos4;
    
}