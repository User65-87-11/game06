#version 330 core
 
layout (location = 0) in vec4 xy_uv;
 
 
out vec2 TexCoords;

uniform mat4 ortho;
uniform mat4 translate;
uniform float rotation;

void main()
{	
 

	vec4 orto_pos = ortho  *translate* vec4(xy_uv.xy,0.0,1.0);
    gl_Position = vec4(orto_pos.x,orto_pos.y*rotation,orto_pos.zw);
	

    TexCoords = xy_uv.zw;
}