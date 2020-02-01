#version 330 core
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;
uniform float uvScale;

in vec3 Color;
in vec2 TexCoord;

out vec4 FragColor;

void main(){
        FragColor = mix(texture(texture1,TexCoord),texture(texture2,TexCoord * uvScale), mixValue);
}