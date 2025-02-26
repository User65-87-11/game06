#version 330 core
layout (location = 0) in vec2 vpos;


out vec4 fcolor;

uniform mat4 projection;
uniform vec3 view_pos;

void main()
{
 
  	gl_Position = projection *   vec4(  vpos,0.0f ,1.0);
 
	 
    fcolor = vec4(0.2,0.3,1.0,0.4);
}