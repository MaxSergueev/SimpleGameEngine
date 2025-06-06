#version 400 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 32) out; // Increased slightly

in vec3 worldPos[];
in vec3 worldNormal[];
in vec2 texCoord[];
in float height[];

out vec3 fragWorldPos;
out vec3 fragWorldNormal;
out vec2 fragTexCoord;
out float fragHeight;
out vec3 fragColor;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform float uTime;

void emitTree(vec3 basePos, vec3 normal, float treeHeight) {
    vec3 up = normal;
    vec3 right = normalize(cross(up, vec3(0, 1, 0)));
    vec3 forward = normalize(cross(up, right));
    
    float trunkRadius = 0.008;
    float trunkHeight = treeHeight * 0.4;
    float coneRadius = 0.04;
    
    vec3 trunkTop = basePos + up * trunkHeight;
    vec3 coneTop = basePos + up * treeHeight;
    
    // === TRUNK (4-sided) ===
    fragColor = vec3(0.4, 0.2, 0.1);
    
    vec3 corners[4] = vec3[](
        right + forward,
        -right + forward, 
        -right - forward,
        right - forward
    );
    
    for (int i = 0; i < 4; i++) {
        vec3 dir1 = normalize(corners[i]) * trunkRadius;
        vec3 dir2 = normalize(corners[(i + 1) % 4]) * trunkRadius;
        
        // Trunk face as triangle strip
        fragWorldPos = basePos + dir1;
        fragWorldNormal = normalize(dir1);
        fragHeight = length(basePos);
        gl_Position = vec4(fragWorldPos, 1.0) * uWorldTransform * uViewProj;
        EmitVertex();
        
        fragWorldPos = trunkTop + dir1;
        fragWorldNormal = normalize(dir1);
        gl_Position = vec4(fragWorldPos, 1.0) * uWorldTransform * uViewProj;
        EmitVertex();
        
        fragWorldPos = basePos + dir2;
        fragWorldNormal = normalize(dir2);
        gl_Position = vec4(fragWorldPos, 1.0) * uWorldTransform * uViewProj;
        EmitVertex();
        
        fragWorldPos = trunkTop + dir2;
        fragWorldNormal = normalize(dir2);
        gl_Position = vec4(fragWorldPos, 1.0) * uWorldTransform * uViewProj;
        EmitVertex();
        
        EndPrimitive();
    }
    
    // === CONE (4 separate triangles) ===
    fragColor = vec3(0.1, 0.4, 0.1);
    
    // Each cone face as a separate triangle
    for (int i = 0; i < 4; i++) {
        vec3 dir1 = normalize(corners[i]) * coneRadius;
        vec3 dir2 = normalize(corners[(i + 1) % 4]) * coneRadius;
        
        // Single triangle: base1 -> base2 -> top
        fragWorldPos = trunkTop + dir1;
        fragWorldNormal = normalize(dir1 + up * 0.8);
        gl_Position = vec4(fragWorldPos, 1.0) * uWorldTransform * uViewProj;
        EmitVertex();
        
        fragWorldPos = trunkTop + dir2;
        fragWorldNormal = normalize(dir2 + up * 0.8);
        gl_Position = vec4(fragWorldPos, 1.0) * uWorldTransform * uViewProj;
        EmitVertex();
        
        fragWorldPos = coneTop;
        fragWorldNormal = up;
        gl_Position = vec4(fragWorldPos, 1.0) * uWorldTransform * uViewProj;
        EmitVertex();
        
        EndPrimitive(); // End each triangle separately
    }
}

void main()
{
    // First emit the original triangle (terrain)
    for (int i = 0; i < 3; i++) {
        fragWorldPos = worldPos[i];
        fragWorldNormal = worldNormal[i];
        fragTexCoord = texCoord[i];
        fragHeight = height[i];
        fragColor = vec3(1.0);
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
    
    // Tree placement
    vec3 triangleCenter = (worldPos[0] + worldPos[1] + worldPos[2]) / 3.0;
    vec2 centerTexCoord = (texCoord[0] + texCoord[1] + texCoord[2]) / 3.0;
    
    float quickRandom = fract(sin(dot(centerTexCoord, vec2(12.9898, 78.233))) * 43758.5453);
    if (quickRandom < 0.98) return;
    
    float centerHeight = (height[0] + height[1] + height[2]) / 3.0;
    float normalizedHeight = (centerHeight - 0.8) / 0.4;
    normalizedHeight = clamp(normalizedHeight, 0.0, 1.0);
    
    // UPDATED: Trees now spawn on the new green area (0.7-0.9 range)
    if (normalizedHeight >= 0.7 && normalizedHeight < 0.9) {
        vec3 centerNormal = normalize((worldNormal[0] + worldNormal[1] + worldNormal[2]) / 3.0);
        float treeHeight = 0.08 + quickRandom * 0.04;
        emitTree(triangleCenter, centerNormal, treeHeight);
    }
}








