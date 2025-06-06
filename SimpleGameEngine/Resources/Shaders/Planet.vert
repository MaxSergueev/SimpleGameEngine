#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform float uTime;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;

void main()
{
    // Create rotation matrix for Y-axis rotation
    float rotationSpeed = 0.5;
    float angle = uTime * rotationSpeed;
    
    mat3 rotationMatrix = mat3(
        cos(angle), 0.0, sin(angle),
        0.0,        1.0, 0.0,
        -sin(angle), 0.0, cos(angle)
    );
    
    // Apply rotation to position and normal
    vec3 rotatedPosition = rotationMatrix * position;
    vec3 rotatedNormal = rotationMatrix * normal;
    
    vPosition = rotatedPosition;
    vNormal = rotatedNormal;
    vTexCoord = texCoord;
    
    gl_Position = vec4(rotatedPosition, 1.0);
}


