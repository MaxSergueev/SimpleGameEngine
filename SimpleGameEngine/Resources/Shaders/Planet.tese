#version 400 core

layout(triangles, equal_spacing, ccw) in;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform sampler2D uNoiseTexture;
uniform float uDisplacementStrength = 0.2;

in vec3 tcPosition[];
in vec3 tcNormal[];
in vec2 tcTexCoord[];

out vec3 worldPos;
out vec3 worldNormal;
out vec2 texCoord;
out float height;

void main()
{
    // Interpolate using barycentric coordinates
    vec3 p0 = gl_TessCoord.x * tcPosition[0];
    vec3 p1 = gl_TessCoord.y * tcPosition[1];
    vec3 p2 = gl_TessCoord.z * tcPosition[2];
    vec3 tessellatedPos = p0 + p1 + p2;
    
    // Interpolate texture coordinates
    vec2 t0 = gl_TessCoord.x * tcTexCoord[0];
    vec2 t1 = gl_TessCoord.y * tcTexCoord[1];
    vec2 t2 = gl_TessCoord.z * tcTexCoord[2];
    vec2 interpolatedTexCoord = t0 + t1 + t2;
    
    // Normalize to keep it spherical
    tessellatedPos = normalize(tessellatedPos);
    
    // Sample noise and displace
    float noise = texture(uNoiseTexture, interpolatedTexCoord).r;
    vec3 displacedPos = tessellatedPos + tessellatedPos * noise * uDisplacementStrength;
    
    height = length(displacedPos);
    worldPos = displacedPos;
    worldNormal = normalize(displacedPos);
    texCoord = interpolatedTexCoord;
    
    gl_Position = vec4(displacedPos, 1.0) * uWorldTransform * uViewProj;
}






