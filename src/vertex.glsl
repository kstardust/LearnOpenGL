#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;


out vec3 color;
out vec2 texCoord;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    texCoord = aTexCoord;
}
