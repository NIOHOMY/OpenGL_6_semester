#version 330 core

out vec4 fragcolor;
in vec3 ourColor;
in vec2 ourTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    vec4 color1 = texture(texture1, ourTexCoord);
    vec4 color2 = texture(texture2, ourTexCoord);
    
    fragcolor = color1*color2;//mix(color1, color2, 0.5);
};