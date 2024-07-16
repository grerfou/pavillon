#version 330 core

in vec2 texCoord;
in vec3 fragNormal;

out vec4 fragColor;

uniform sampler2D displacementMap;

void main(void)
{
    // Obtenez la couleur de la texture de displacement aux coordonnées de texture
    vec4 displacementColor = texture(displacementMap, texCoord);
    
    // Définir la couleur de sortie avec la couleur de la texture de displacement
    fragColor = displacementColor;
}

