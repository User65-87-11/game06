#version 330 core


in vec4 inColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture0;


void main(){
	vec4 col = texture(texture0, TexCoord);
	if(col.x < 0.01)
	{
		FragColor = vec4(0.0f,0.0f,0.0f,0.0f);
	}else
	{
			FragColor = col;
	}	
	
} 