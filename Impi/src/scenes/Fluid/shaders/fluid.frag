#version 430

struct Blob
{
	vec2 pos;
	vec2 vel;
	float r;
	float mass;
	float pad;
}; //std430


layout(std430, binding = 0) buffer BlobBuffer {
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



void main() {

    vec2 uv = gl_FragCoord.xy / resolution;

    vec3 color = vec3(0.0);

    for (int i = 0; i < numBlobs; i++)
    {
        float d = sdCircle(uv, blobs[i].pos, blobs[i].r);
        if (d < 0.0)
            color += vec3(0.0, 0.0, 0.3); 
    }

    FragColor = vec4(color, 1.0);
}