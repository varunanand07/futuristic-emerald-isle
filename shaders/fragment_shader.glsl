#version 330 core
out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords; // From Vertex Shader


uniform sampler2D texture1;


uniform vec3 lightPos; 
uniform vec3 lightColor;


uniform vec3 viewPos;


uniform vec3 objectColor;


uniform vec3 fogColor;
uniform float fogDensity;

void main()
{
    
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;
  	
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    
    float specularStrength = 1.0;
    float shininess = 64.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;  
    
    
    vec3 texColor = texture(texture1, TexCoords).rgb;
    
    // Combine all lighting components with texture and object color
    vec3 result = (ambient + diffuse + specular) * texColor * objectColor;
    
    
    float distance = length(viewPos - FragPos);
    float fogFactor = 1.0 / exp((distance * fogDensity) * (distance * fogDensity));
    fogFactor = clamp(fogFactor, 0.0, 1.0);
    vec3 finalColor = mix(fogColor, result, fogFactor);
    
    FragColor = vec4(finalColor, 1.0);
}
