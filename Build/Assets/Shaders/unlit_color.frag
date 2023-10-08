#version 430

in layout(location = 0) vec3 color;

out layout(location = 0) vec4 ocolor;

uniform float time;

void main()
{
	vec3 ncolor = vec3(color * sin(time));
	ocolor = vec4(ncolor, 1);
}
