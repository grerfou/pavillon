#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTexCoord;
layout (location = 2) in vec3 vertexNormal;

out vec2 texCoord;
out vec3 fragNormal;

void main(void)
{
    gl_Position = vec4(vertexPosition, 1.0);
    texCoord = vertexTexCoord;
    fragNormal = vertexNormal;
}

