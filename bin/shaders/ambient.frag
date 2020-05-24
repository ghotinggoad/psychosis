#version 460 core


in vec3 FragPos;
in vec3 Normal;

uniform vec3 color;
uniform vec3 lightColor;
uniform vec3 lightPosition;

out vec4 FragColor;

void main(){
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * color;
    vec3 result = ambient * lightColor;

    FragColor = vec4(result, 1.0f);
}