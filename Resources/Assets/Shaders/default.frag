#version 450 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;
layout (std140, binding = 0) uniform ViewProj
{
    mat4 view;
    mat4 proj;
}; 
uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}