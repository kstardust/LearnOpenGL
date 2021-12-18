#version 330 core
out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D ufTexture;
uniform sampler2D ufTexture2;
uniform vec3 lightColor;
uniform vec3 objColor;

uniform vec4 ufColor;

void main()
{
  // FragColor = mix(texture(ufTexture, texCoord), texture(ufTexture2, texCoord), 0.2);
  FragColor = vec4(objColor * lightColor, 1.0);
  //FragColor = texture(ufTexture, texCoord);
}
