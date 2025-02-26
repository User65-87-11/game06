#version 330 core
in vec4 fs_color;
in vec2 fs_texture_coords;
out vec4 FragColor;


uniform sampler2D tx_texture;
 

void main()
{    
 
   // FragColor  =  fs_color;
    FragColor  = texture(tx_texture,fs_texture_coords)  ;

	if(FragColor.a < 0.01)
	{
		FragColor = vec4(fs_color.rgb,0.5f);
	}
}