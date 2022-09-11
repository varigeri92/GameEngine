#version 450 core
layout (location = 0) in vec3 _Pos;
layout (location = 1) in vec3 _Color;
layout (location = 2) in vec2 _TexCoord;
layout (location = 3) in vec3 _Normal;

out vec3 VertexColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos; 


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

layout (std140, binding = 2) uniform ambient
{
    vec4 ambientColor;
};


uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(_Pos, 1.0);
    VertexColor = _Color;
    Normal = mat3(transpose(inverse(model))) * _Normal;
    TexCoord = _TexCoord;
}