#version 330 core
layout (location = 0) in vec3 vpos;
layout (location = 1) in vec4 vcolor;
layout (location = 2) in vec2 texture_coords;
layout (location = 3) in mat4 local_model;
 


out vec4 fs_color;
out vec2 fs_texture_coords;
 

uniform mat4 projection;
uniform mat4 cam_view;
uniform vec4 cam_pos;
uniform mat4 base_model;

layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
 

void main()
{
 
 
  	gl_Position = projection* 
	cam_view * 
	base_model* 
	local_model *
	vec4(vpos  ,1.0);
 
	 
    fs_color = vcolor;
	fs_texture_coords = texture_coords;
}