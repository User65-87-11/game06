#version 430 core

layout (location = 0) in vec3 vpos;
layout (location = 1) in vec4 vcol;
layout (location = 2) in vec2 texture_coords;
layout (location = 3) in mat4 model;
 // +4,5,6
layout (location = 10) in int model_id;

out vec4 frag_color;
flat out int frag_model_id;


layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
	
};


 

 

void main()
{
 
   	gl_Position =projection * view * model * vec4(vpos  ,1.0) ;
	
    frag_color = vcol;
	 if(model_id > 1024)
	 {
			frag_model_id = 5;
	}else{
		frag_model_id = model_id;
	}
	
}