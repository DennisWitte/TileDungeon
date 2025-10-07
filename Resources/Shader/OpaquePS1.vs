#version 330 core

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

uniform mat4 mvp;
uniform mat4 matView;
uniform mat4 matModel;

noperspective out vec2 vTexCoord;
out vec4 vColor;
out float vViewZ;

void main()
{
    vTexCoord = vertexTexCoord;
    vColor = vertexColor;

    vec4 worldPos = matModel * vec4(vertexPosition, 1.0);
    vec4 viewPos = matView * worldPos;

    vViewZ = -viewPos.z;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
