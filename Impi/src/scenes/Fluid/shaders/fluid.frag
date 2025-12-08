#version 430

layout(std140, binding = 0) uniform ViewUniforms
{   mat4 view;
    mat4 projection;
    vec3 cameraPos;
    float padding;
};

struct Blob
{
	vec3 pos;
	vec3 vel;
	float r;
	float mass;
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
    vec3 ndc = clip.xyz / clip.w;       // perspective divide
    return ndc.xy * 0.5 + 0.5;          // map from [-1,1] -> [0,1]
}


void main() {

    vec2 uv = gl_FragCoord.xy / resolution;

    vec3 color = vec3(0.0);

    for (int i = 0; i < numBlobs; i++)
    {
        
        vec2 blobUV = worldToUV(blobs[i].pos);

        vec4 offset = projection * view * vec4(blobs[i].pos + vec3(blobs[i].r,0,0),1.0);
        offset /= offset.w;
        float screenRadius = abs(blobUV.x - (offset.x*0.5 + 0.5));
        float d = sdCircle(uv, blobUV, screenRadius);
        if (d < 0.0)
            color += vec3(0.0, 0.0, 0.3); 
    }

    FragColor = vec4(color, 1.0);
}