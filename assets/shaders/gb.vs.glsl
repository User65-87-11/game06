#version 330 core
layout (location = 0) in vec2 vpos;
layout (location = 1) in vec3 vcol;
layout (location = 2) in vec3 vfog;
layout (location = 3) in vec2 vpos_off;
out vec3 fcolor;
out vec3 ffogcol;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
 
   	gl_Position = projection* view * model *vec4(vpos +vpos_off ,0.0,1.0);
 
    fcolor = vcol;
	ffogcol = vfog;
}