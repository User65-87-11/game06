#version 330 core

in vec4 inColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main(){

    vec4 color0 = texture(texture0, TexCoord);
    vec4 color1 = texture(texture1, TexCoord);
	vec4 color2 = inColor;
 
    if (color1.a > 0.0) {
        FragColor = color1;  
    } else {
        FragColor = color0;  
    }
	
 
} 