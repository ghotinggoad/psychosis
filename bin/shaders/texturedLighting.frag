#version 460 core


in vec2 TexCoord;
in vec3 FragPosition;
in vec3 Normal;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform sampler2D cubeTexture;

out vec4 FragColor;

void main(){
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPosition - FragPosition); 
    float diff = max(dot(norm, lightDirection), 0.0f);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5f;
    vec3 cameraPosition = normalize(cameraPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);

    float spec = pow(max(dot(cameraPosition, reflectDirection), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor; 


    vec3 result = (ambient + diffuse + specular) * texture(cubeTexture, TexCoord).rgb;

    FragColor = vec4(result, 1.0f);
}