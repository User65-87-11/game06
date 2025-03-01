#version 430 core

in vec4 frag_color;
in vec2 fs_texture_coords;


out vec4 out_color;

uniform sampler2D tx_texture;


void main()
{    
  
 
	//out_color = frag_color;

	out_color  = texture(tx_texture,fs_texture_coords)  ;
 
}