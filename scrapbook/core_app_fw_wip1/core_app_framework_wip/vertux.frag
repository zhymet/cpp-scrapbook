// Primitive Object Fragment Shader

#version 330 core

out vec4 color;
in vec2 vert_out_texture_pos;
uniform sampler2D frag_texture;
uniform vec3 frag_base_color;

void main()
{
	color = vec4(frag_base_color, 1.0); // Base Color
    color = texture(frag_texture, vert_out_texture_pos) + vec4(frag_base_color, 1.0); // Texture Layer 1
}