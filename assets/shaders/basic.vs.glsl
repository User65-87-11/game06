#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;

uniform mat4 projection;

out vec3 fragColor;
void main()
{
    gl_Position =  projection *  vec4(aPos,0.0f, 1.0f);
    fragColor =  aCol;
}