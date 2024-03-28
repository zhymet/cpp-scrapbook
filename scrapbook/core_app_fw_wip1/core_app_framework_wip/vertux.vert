// Primitive Object Vertex Shader

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 vert_texture_pos;

out vec2 vert_out_texture_pos;

uniform mat4 projection; 
uniform mat4 model;

void main()
{
   // note that we read the matrix multiplication from right to left
   gl_Position = projection * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   vert_out_texture_pos = vert_texture_pos;
}