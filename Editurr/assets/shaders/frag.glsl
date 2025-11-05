#version 330 core
in vec2 o_TexCoords;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, o_TexCoords);
} 