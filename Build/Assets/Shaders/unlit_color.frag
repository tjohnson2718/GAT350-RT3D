#version 430

in layout(location = 0) vec3 color;

out layout(location = 0) vec4 ocolor;

void main()
{
	ocolor = vec4(color, 1);
}
