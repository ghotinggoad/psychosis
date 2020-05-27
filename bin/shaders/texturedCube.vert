#version 460 core


layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat3 normalMatrixTransform;

out vec3 FragPosition;
out vec3 Normal;
out vec2 TexCoord;

void main(){
    // note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(aPosition, 1.0f);
    FragPosition = vec3(model * vec4(aPosition, 1.0));
    Normal = normalMatrixTransform * aNormal;  
    TexCoord = aTexCoord;
}