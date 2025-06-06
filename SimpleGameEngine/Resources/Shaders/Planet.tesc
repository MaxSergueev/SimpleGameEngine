#version 400 core

layout(vertices = 3) out;

uniform float uTessLevelInner = 4.0;
uniform float uTessLevelOuter = 4.0;

in vec3 vPosition[];
in vec3 vNormal[];
in vec2 vTexCoord[];

out vec3 tcPosition[];
out vec3 tcNormal[];
out vec2 tcTexCoord[];

void main()
{
    if (gl_InvocationID == 0) {
        gl_TessLevelInner[0] = uTessLevelInner;
        gl_TessLevelOuter[0] = uTessLevelOuter;
        gl_TessLevelOuter[1] = uTessLevelOuter;
        gl_TessLevelOuter[2] = uTessLevelOuter;
    }
    
    // Pass through the vertex data
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tcPosition[gl_InvocationID] = vPosition[gl_InvocationID];
    tcNormal[gl_InvocationID] = vNormal[gl_InvocationID];
    tcTexCoord[gl_InvocationID] = vTexCoord[gl_InvocationID];
}


