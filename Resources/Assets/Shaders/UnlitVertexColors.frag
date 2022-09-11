#version 450 core
out vec4 FragColor;
  
in vec3 VertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D u_Texture;

layout (std140, binding = 0) uniform ViewProj
{
    mat4 view;
    mat4 proj;
};

layout (std140, binding = 1) uniform Lights
{
    vec4 direction;
    vec4 color;
}; 

vec4 ambient = vec4(1, 1, 1, 1);
void main()
{
    vec3 norm = normalize(Normal);
    vec3 ligthtdir = normalize(direction.xyz);
    float light = dot(norm, ligthtdir);
    light *= color.w;

    vec4 outColor = (vec4(VertexColor, 1) * light) + (vec4(ambient.xyz, 1 ) * ambient.w);
    
    FragColor = vec4(VertexColor, 1); // texture(u_Texture, TexCoord) * color * outColor;
}