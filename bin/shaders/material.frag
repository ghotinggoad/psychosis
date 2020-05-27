#version 460 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPosition;  
in vec3 Normal;  
  
uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPosition);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 cameraDirection = normalize(cameraPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);  
    float spec = pow(max(dot(cameraDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 