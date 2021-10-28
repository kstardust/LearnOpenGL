#version 330 core
out vec4 FragColor;
in vec3 color;

uniform vec4 ufColor;
void main()
{
    FragColor = vec4(color.xyz, 1.0f);
}