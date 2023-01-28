#version 460 core


in vec3 Norm;
in vec3 Pos;

out vec4 FragCol;


uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;

uniform vec3 LightPos;
uniform float LightIntensity;

uniform vec3 CamPos;


void main()
{
    // Ambient
    vec3 A = LightIntensity * Ambient;

    // Diffuse
    vec3 N = normalize(Norm);
    vec3 LightDir = normalize(LightPos - Pos);
    float DiffScale = max(dot(N, LightDir), 0.0);
    vec3 D = LightIntensity * (DiffScale * Diffuse);

    // Specular
    vec3 ViewDir = normalize(CamPos - Pos);
    vec3 ReflectDir = reflect(-LightDir, N);
    float SpecScale = pow(max(dot(ViewDir, ReflectDir), 0.0), Shininess);
    vec3 S = LightIntensity * (SpecScale * Specular);

    // Result
    FragCol = vec4(A + D + S, 1.0f);
}