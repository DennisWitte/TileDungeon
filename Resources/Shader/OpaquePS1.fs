#version 330 core

noperspective in vec2 vTexCoord;
in vec4 vColor;
in float vViewZ;

uniform sampler2D texture0;

uniform float paletteBits;
uniform float ditherStrength;
uniform vec3 fogColor;
uniform float fogStart;
uniform float fogEnd;

out vec4 fragColor;

float bayerDither(vec2 uv)
{
    vec2 p = fract(uv * 2.0);
    float m = (p.x < 0.5) ? (p.y < 0.5 ? 0.0 : 0.75) : (p.y < 0.5 ? 0.5 : 0.25);
    return m / 255.0;
}

void main()
{
    vec4 tex = texture(texture0, vTexCoord);
    vec4 col = tex * vColor;

    float d = ditherStrength * bayerDither(gl_FragCoord.xy);

    float levels = pow(2.0, paletteBits) - 1.0;
    vec3 q = floor((col.rgb + d) * levels + 0.5) / levels;

    vec3 baseColor = q;
    float alpha = col.a;

    float fogFactor = clamp((fogEnd - vViewZ) / (fogEnd - fogStart), 0.0, 1.0);
    vec3 finalColor = mix(fogColor, baseColor, fogFactor);

    fragColor = vec4(finalColor, alpha);
}
