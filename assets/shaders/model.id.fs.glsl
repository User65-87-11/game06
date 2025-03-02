#version 430 core

flat in vec4 fs_obj_id;

out vec4 out_color;


void main()
{    
 
	out_color =  fs_obj_id;
	
}