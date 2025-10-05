// lightmap.fs
#version 330

in vec2 fragTexCoord;
in vec2 fragTexCoord2;
in vec4 fragColor;

uniform sampler2D texture0; // Diffuse
uniform sampler2D texture1; // Lightmap
uniform vec4 colDiffuse;    // Materialfarbe (colDiffuse vom Model/Material)

out vec4 finalColor;

void main()
{
    vec4 base = texture(texture0, fragTexCoord) * colDiffuse;
    vec4 lm   = texture(texture1, fragTexCoord2);
    finalColor = base  * fragColor; // Diffuse * Lightmap * VertexColor
}
