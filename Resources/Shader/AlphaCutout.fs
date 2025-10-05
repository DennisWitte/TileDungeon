#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform float alphaThreshold;

out vec4 finalColor;

void main() {
    vec4 texColor = texture(texture0, fragTexCoord);

    if (texColor.a < alphaThreshold)
        discard;

    finalColor = texColor * fragColor;
}
