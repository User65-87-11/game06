#version 330 core
in vec3 fcolor;
in vec3 ffogcol;
out vec4 FragColor;

 

void main()
{    
 
	FragColor = vec4(fcolor * ffogcol,1.0);
   // FragColor = vec4(1.0f,0.2f,0.3f,1.0f);
}