#version 330 core
layout (location = 0) in vec2 vpos;
layout (location = 1) in float alpha;
layout (location = 2) in vec2 offset;


out vec4 frag_col ;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


 
void main()
{
 
  	gl_Position = projection* view * model *vec4(vpos+offset,0.0,1.0);
	frag_col = vec4(0.1,0.0,0.0,alpha);
}