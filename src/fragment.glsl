#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D ufTexture;
uniform sampler2D ufTexture2;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 objColor;
uniform vec3 viewPos;

uniform vec4 ufColor;

void main()
{
  // FragColor = mix(texture(ufTexture, texCoord), texture(ufTexture2, texCoord), 0.2);
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;

  float specularStrength = 0.5;
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-viewDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * lightColor;

  vec3 result = (ambient + diff + specular) * objColor;
  
  FragColor = vec4(result, 1.0);

  //FragColor = texture(ufTexture, texCoord);
}
