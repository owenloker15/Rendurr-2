#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec3 o_Normal;
out vec3 o_FragPos;
out vec2 o_TexCoord;

uniform mat4 u_Transform;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_Transform * vec4(a_Pos, 1.0);
    o_FragPos = vec3(u_Transform * vec4(a_Pos, 1.0));
    o_Normal = mat3(transpose(inverse(u_Transform))) * a_Normal;  
    o_TexCoord = a_TexCoord;
}
