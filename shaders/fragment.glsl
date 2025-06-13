#version 330 core

out vec4 FragColor;

flat in vec3 NormalFlat;
in vec3 NormalSmooth;
in vec3 FragPos;
in vec2 TexCoord;

uniform vec3 viewPos;
uniform bool lightingEnabled;
uniform bool shadingEnabled;
uniform vec3 lightDir;
uniform vec3 lightColor;

uniform sampler2D texture1;

void main() {
    vec3 color = texture(texture1, TexCoord).rgb;

    if (!lightingEnabled) {
        FragColor = vec4(color, 1.0);
        return;
    }

    vec3 norm = normalize(shadingEnabled ? NormalSmooth : NormalFlat);
    vec3 light = normalize(-lightDir);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 ambient = 0.2 * color;

    float diff = max(dot(norm, light), 0.0);
    vec3 diffuse = diff * color;

    vec3 reflectDir = reflect(-light, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = 0.3 * spec * lightColor;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
