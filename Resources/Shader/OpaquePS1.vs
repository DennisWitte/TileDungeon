#version 330 core

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

uniform mat4 mvp;        // model-view-projection
uniform mat4 matView;    // Raylib liefert "matView" wenn du es setzt
uniform mat4 matModel;   // Weltmatrix

out noperspective vec2 vTexCoord;
out vec4 vColor;
out float vViewZ;

void main()
{
    vTexCoord = vertexTexCoord;
    vColor = vertexColor;

    // Berechne Position im Clip-Space
    vec4 worldPos = matModel * vec4(vertexPosition, 1.0);
    vec4 viewPos = matView * worldPos;

    vViewZ = -viewPos.z; // Kamera schaut -Z, daher negativ
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}
