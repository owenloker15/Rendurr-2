#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoords;

out vec2 o_TexCoords;

uniform mat4 u_Transform;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_Transform * vec4(a_Pos, 1.0);
    o_TexCoords = a_TexCoords;
}