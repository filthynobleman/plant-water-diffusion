#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;


out vec3 Norm;
out vec3 Pos;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Proj;
uniform mat3 InvModel;


void main()
{
    gl_Position = Proj * (View * (Model * vec4(aPos, 1.0)));
    Norm = InvModel * aNorm;
}