#version 330 core

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture1;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform bool lightingEnabled;
uniform bool shadingEnabled;

void main() {
    vec3 texColor = texture(texture1, TexCoord).rgb;

    if (!lightingEnabled) {
        FragColor = vec4(texColor, 1.0);
        return;
    }

    // Cieniowanie p³askie vs g³adkie
    vec3 norm = shadingEnabled ? normalize(Normal) : vec3(0.0, 0.0, 1.0);
    vec3 light = normalize(-lightDir);

    vec3 ambient = 0.1 * lightColor;
    float diff = max(dot(norm, light), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * texColor;
    FragColor = vec4(result, 1.0);
}
