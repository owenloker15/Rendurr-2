#version 330 core

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 Red;

in vec3 o_Normal;
in vec3 o_FragPos;
in vec2 o_TexCoord;

uniform vec3 u_ViewPos;
uniform sampler2D u_Material_albedo;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

void main()
{
    // Ambient
    vec3 ambientColor = light.ambient * material.ambient;
    
    // Diffuse
    vec3 normal = normalize(o_Normal);
    vec3 lightDir = normalize(light.position - o_FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseColor = light.diffuse * (diff * material.diffuse);

    // Specular
    vec3 viewDir = normalize(u_ViewPos - o_FragPos);
    vec3 lightReflectionDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, lightReflectionDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    //Texture Sampling
    vec4 texColor = texture(u_Material_albedo, o_TexCoord);
    
    // Final output
    vec3 result = ambientColor + diffuseColor + specular;
    FragColor = vec4(result, 1.0);
    
    // Test shader output
    Red = vec4(1.0, 0.0, 0.0, 1.0);
}
