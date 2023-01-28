#version 330 core
out vec4 FragColor;

struct Material_t 
{
    vec3    Ambient;
    vec3    Diffuse;
    vec3    Specular;    
    float   Shininess;
}; 

struct Light_t 
{
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

in vec3 FragPos;  
in vec2 UV;
in vec3 Normal;  
  
uniform vec3 ViewPos;
uniform Material_t Material;
uniform Light_t Light;

void main()
{
    // ambient
    vec3 Ambient = Light.Ambient * Material.Ambient;
  	
    // diffuse 
    vec3 Norm = normalize(Normal);
    vec3 LightDir = normalize(Light.Position - FragPos);
    float Diff = max(dot(Norm, LightDir), 0.0);
    vec3 Diffuse = Light.Diffuse * (Diff * Material.Diffuse);
    
    // specular
    vec3 ViewDir = normalize(ViewPos - FragPos);
    vec3 ReflectDir = reflect(-LightDir, Norm);  
    float Spec = pow(max(dot(ViewDir, ReflectDir), 0.0), Material.Shininess);
    vec3 Specular = Light.Specular * (Spec * Material.Specular);  
        
    vec3 Result = Ambient + Diffuse + Specular;
    FragColor = vec4(Result, 1.0);
} 