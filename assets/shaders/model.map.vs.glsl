#version 430 core

layout (location = 0) in vec3 vpos;
layout (location = 1) in vec4 vcol;
layout (location = 2) in vec2 texture_coords;
layout (location = 3) in mat4 model;
 // +4,5,6
 
layout (location = 7) in vec3 normal;

out vec4 frag_color;
 


layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
	
};


 

 

void main()
{
 
   	gl_Position =projection * view * model * vec4(vpos  ,1.0) ;
	
    frag_color = vcol;
	 
	
}