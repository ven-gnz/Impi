#version 330 core


in vec3 near;
in vec3 far;

out vec4 outColor;

vec4 check_near_far(vec3 nearVal, vec3 farVal) {
    bool nearNaN  = any(isnan(nearVal));
    bool nearInf  = any(isinf(nearVal));
    bool farNaN   = any(isnan(farVal));
    bool farInf   = any(isinf(farVal));

    if (nearNaN || farNaN) {
        
        return vec4(1.0, 1.0, 0.0, 1.0);
    } 
    else if (nearInf || farInf) {
        
        return vec4(1.0, 0.0, 1.0, 1.0);
    } 
    else {
        
        float t = clamp((nearVal.y + 1.0) * 0.5, 0.0, 1.0);
        return vec4(t, 1.0 - t, 0.0, 1.0);
    }
}

void main() {

    float t = -near.y / (far.y - near.y);
    
    outColor = vec4(1.0, 0.0, 0.0, 1.0 * float(t > 0)); // opacity = 1 when t > 0, opacity = 0 otherwise
 
 }
