#version 330

in vec2 fragTexCoord;
out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
   vec4 texColor = texture(uTexture, fragTexCoord);
   texColor.r += 0.2;
   outColor = texColor;
}