#version 330 core


in vec3 near;
in vec3 far;

out vec4 outColor;

void main() {
    bool nearNaN  = any(isnan(near));
    bool nearInf  = any(isinf(near));
    bool farNaN   = any(isnan(far));
    bool farInf   = any(isinf(far));

    if (nearNaN || farNaN) {
        // Bright yellow for NaN
        outColor = vec4(1.0, 1.0, 0.0, 1.0);
    } 
    else if (nearInf || farInf) {
        // Magenta for infinity
        outColor = vec4(1.0, 0.0, 1.0, 1.0);
    } 
    else {
        // Visualize Y-coordinate of near as red/green gradient
        float t = clamp((near.y + 1.0) * 0.5, 0.0, 1.0);
        outColor = vec4(t, 1.0 - t, 0.0, 1.0);
    }
}