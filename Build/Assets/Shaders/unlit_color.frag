#version 430

in layout(location = 0) vec3 color;

out layout(location = 0) vec4 ocolor;

uniform float time;

void main()
{
	vec3 ncolor = vec3((color.r + color.g + color.b) / 3);
	ocolor = vec4(ncolor, 1);
}
