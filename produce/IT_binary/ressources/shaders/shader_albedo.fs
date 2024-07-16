#version 330 core

in vec2 texCoord;
in vec3 fragNormal;

out vec4 fragColor;

uniform sampler2D albedoMap;

void main(void)
{
    // Obtenez la couleur de la texture albedo aux coordonnées de texture
    vec4 albedoColor = texture(albedoMap, texCoord);
    
    // Définir la couleur de sortie avec la couleur de la texture albedo
    fragColor = albedoColor;
}

