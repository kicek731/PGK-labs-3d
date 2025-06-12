#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec4 worldPosition = model * vec4(aPos, 1.0);
    FragPos = worldPosition.xyz;

    // Sztuczna normalna w kierunku Z (do testów)
    Normal = mat3(transpose(inverse(model))) * vec3(0.0, 0.0, 1.0);

    TexCoord = aTexCoord;
    gl_Position = projection * view * worldPosition;
}
