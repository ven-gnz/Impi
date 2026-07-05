#version 420 core

in vec3 norm;
in vec3 col;

out vec4 fragColor;

vec3 lightDir = vec3(0, -5, 0);

void main()
{
	float d = max(dot(normalize(norm), normalize(lightDir)), 0.0);
	vec3 shading = col * (0.15 + 0.7 * d);
	fragColor = vec4(shading,1.0);

}