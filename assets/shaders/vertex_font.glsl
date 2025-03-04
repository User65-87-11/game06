#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aTex;

out vec4 inColor;
out vec2 TexCoord;




void main()
{
    gl_Position =   vec4(aPos, 1.0f);
    inColor =  aCol;
    TexCoord = aTex;
}