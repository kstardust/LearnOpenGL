#version 330 core
out vec4 FragColor;
in vec3 color;
in vec2 texCoord;

uniform sampler2D ufTexture;
uniform sampler2D ufTexture2;

uniform vec4 ufColor;
void main()
{
  FragColor = mix(texture(ufTexture, texCoord), texture(ufTexture2, texCoord), 0.2);
  //FragColor = texture(ufTexture, texCoord);
}
