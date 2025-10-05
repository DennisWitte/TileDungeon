// lightmap.vs
#version 330

// Verwende genau diese Namen (raylib bindet sie automatisch)
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;
in vec2 vertexTexCoord2;

out vec2 fragTexCoord;
out vec2 fragTexCoord2;
out vec4 fragColor;

uniform mat4 mvp;

void main()
{
    fragTexCoord  = vertexTexCoord;
    fragTexCoord2 = vertexTexCoord2;
    fragColor     = vertexColor;
    gl_Position   = mvp * vec4(vertexPosition, 1.0);
}
