// Primitive Object Vertex Shader

#version 330 core

layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view; 
uniform mat4 projection; 

void main()
{
   // note that we read the matrix multiplication from right to left
   gl_Position =  projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   ourColor = aColor;
   TexCoord = aTexCoord;
}