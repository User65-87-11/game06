#version 430 core

layout (location = 0) in vec3 vpos;
layout (location = 1) in vec4 vcol;
layout (location = 2) in vec2 texture_coords;
layout (location = 3) in vec3 normal;

layout (location = 10) in mat4 model;
 // +11,12,13
 


out vec4 frag_color;
out vec2 fs_texture_coords;


layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
	
};


 

 

void main()
{
 
   	gl_Position =projection * view * model * vec4(vpos  ,1.0) ;
	
    frag_color = vcol;

	fs_texture_coords = texture_coords;
	 
	
}