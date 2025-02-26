#version 430 core

in vec4 frag_color;
flat in int frag_model_id;

out vec4 out_color;

layout (std140, binding = 1) uniform Mouse
{
    vec2 mouse_coords;
	
};
 
layout (std430, binding=2) buffer shader_data
{ 
  int  ids_buffer[];
  
};


void main()
{    
 
	if(length(mouse_coords - gl_FragCoord.xy) < 5.0)
	{
		int z = int(gl_FragCoord.z * 31.0);
		float f = frag_model_id;
		out_color =vec4(f, 0.0,0.0,1.0);
	 	if(frag_model_id >0 && frag_model_id < 1024)
		{
			out_color =vec4( 0.0, 1.0,0.0,1.0);
		}
		ids_buffer[z] = frag_model_id;
	}
	else
	{
		out_color = frag_color;
	}
	
 
}