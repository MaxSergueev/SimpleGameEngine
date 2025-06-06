#version 400 core

in vec3 fragWorldPos;
in vec3 fragWorldNormal;
in vec2 fragTexCoord;
in float fragHeight;
in vec3 fragColor;

out vec4 fragColor_out;

void main()
{
    // If fragColor is not default (1,1,1), use it (for trees)
    if (fragColor != vec3(1.0)) {
        fragColor_out = vec4(fragColor, 1.0);
        return;
    }
    
    // Height-based terrain coloring with SWAPPED green and brown
    float normalizedHeight = (fragHeight - 0.8) / 0.4;
    normalizedHeight = clamp(normalizedHeight, 0.0, 1.0);
    
    vec3 color;
    if (normalizedHeight < 0.3) {
        color = vec3(0.0, 0.0, 0.5); // Deep water
    } else if (normalizedHeight < 0.5) {
        color = vec3(0.0, 0.3, 0.8); // Shallow water
    } else if (normalizedHeight < 0.7) {
        color = vec3(0.0, 0.3, 0.8); // Now brown
    } else if (normalizedHeight < 0.9) {
        color = vec3(0.2, 0.6, 0.2); // Now green
    } else {
        color = vec3(0.8, 0.8, 0.8); // Mountains
    }
    
    fragColor_out = vec4(color, 1.0);
}







