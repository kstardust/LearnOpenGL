#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec2 aTexCoord;
layout (location = 1) in vec3 aNormal;

out vec3 color; 
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main()
{
    normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    fragPos = vec3(model * vec4(aPos, 1.0));
    // texCoord = aTexCoord;
}
