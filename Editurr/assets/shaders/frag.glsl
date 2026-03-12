in vec3 o_Normals;
in vec2 o_TexCoords;

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 Red;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, o_TexCoords);
    Red = vec4(1.0, 0.0, 0.0, 1.0);
}