#version 430

layout (location = 0) in vec3 vposition;

uniform mat4 model;
uniform mat4 shadowVP;

void main()
{
    gl_Position = shadowVP * model * vec4(vposition, 1.0);
}
