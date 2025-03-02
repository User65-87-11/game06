#version 430 core

layout (location = 0) in vec3 vpos;
layout (location = 1) in vec4 obj_id;
layout (location = 10) in mat4 model;
 
 


flat out vec4 fs_obj_id;
 


layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
	
};

void main()
{
 
   	gl_Position =projection * view * model * vec4(vpos  ,1.0) ;
	
	fs_obj_id = obj_id;
	 
	
}