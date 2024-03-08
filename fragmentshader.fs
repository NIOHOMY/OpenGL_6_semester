#version 330 core
out vec4 fragcolor;
in vec3 ourColor;
in vec2 ourTexCoord;
uniform sampler2D texture1;
void main() {
 fragcolor = texture(texture1, ourTexCoord);
};