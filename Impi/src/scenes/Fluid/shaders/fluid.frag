#version 430

layout(std140, binding = 0) uniform ViewUniforms
{   mat4 view;
    mat4 projection;
    vec3 cameraPos;
    float padding;
};

struct Blob
{
	vec4 pos;
	vec4 vel;
	vec4 properties; // r mass empty empty
}; //std430


layout(std430, binding = 1) buffer BlobBuffer {
    Blob blobs[];
};

uniform vec2 resolution;
uniform int numBlobs;


float sdCircle(vec2 p, vec2 center, float r)
{
    return length(p - center) - r;
}

out vec4 FragColor;
in vec2 uv;

vec2 worldToUV(vec3 worldPos)
{
    vec4 clip = projection * view * vec4(worldPos, 1.0);
    vec3 ndc = clip.xyz / clip.w;
    return ndc.xy * 0.5 + 0.5;
}


void main() {

    vec2 screenUV = gl_FragCoord.xy / resolution;

    vec3 color = vec3(0.0);
    vec3 camRight = vec3(view[0][0], view[1][0], view[2][0]);


    for (int i = 0; i < numBlobs; i++)
    {
        
        vec2 centerUV = worldToUV(blobs[i].pos.xyz);
        float radius = 0.01;
        float d = length(screenUV - centerUV);

        if (d < radius)
            color = vec3(0.0, 0.0, 0.3);
    }
    

    FragColor = vec4(color, 1.0);
    
    }