#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D cubeTexture;

void main(){
    FragColor = texture(cubeTexture, TexCoord) * vec4(ourColor, 1.0f);
}