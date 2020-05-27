#version 460 core


struct Material {
    sampler2D diffuse;
    sampler2D specular;   
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

in vec2 TexCoord;
in vec3 FragPosition;  
in vec3 Normal;  
  
uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;

out vec4 FragColor;

void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPosition);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff *  vec3(texture(material.diffuse, TexCoord));
    
    // specular
    vec3 cameraDirection = normalize(cameraPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);  
    float spec = pow(max(dot(cameraDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
        
    // attenuation
    float distance    = length(light.position - FragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation; 

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 