#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 color;

out layout(location = 0) vec3 ocolor;

void main()
{
	ocolor = color;
	gl_Position = vec4(position, 1.0);
}
