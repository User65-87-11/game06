#version 330 core
layout (location = 0) in vec2 vpos;
layout (location = 1) in vec3 vcol;
layout (location = 2) in vec2 inst_offset;
layout (location = 3) in int object_id;

out vec3 frag_color;
out int object_id;

 
uniform mat4 projection;
uniform mat4 cam_view;
uniform mat4 base_model;

void main()
{
 
	 

   	gl_Position = projection  *  
	cam_view *  
	base_model *   
	vec4(vpos +inst_offset  ,0.0,1.0) ;
	
    frag_color = vcol;
}