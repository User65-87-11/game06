#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text_texture;
uniform vec3 textColor;

void main()
{    
     vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text_texture, TexCoords).r);
     color = vec4(textColor, 1.0) * sampled;

	//color  = vec4(1.0, 1.0, 0.5, 1.0);
}