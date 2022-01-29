#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
  vec3 lightPos;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform sampler2D ufTexture;
uniform sampler2D ufTexture2;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform vec4 ufColor;
uniform Material material;
uniform Light light;

void main()
{
  vec3 ambient = material.ambient * light.ambient;

  // FragColor = mix(texture(ufTexture, texCoord), texture(ufTexture2, texCoord), 0.2);
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(light.lightPos - fragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * material.diffuse * light.diffuse;

  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-viewDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = spec * material.specular * light.specular;

  vec3 result = ambient + diffuse + specular;
  
  FragColor = vec4(result, 1.0);

  //FragColor = texture(ufTexture, texCoord);
}
