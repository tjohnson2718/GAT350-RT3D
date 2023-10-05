#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 color;

out layout(location = 0) vec3 ocolor;

uniform float time;


void main()
{
	ocolor = color;

	float xo = sin(time * 3 + position.y) * 0.5;

	gl_Position = vec4(position + vec3(xo, 0, 0), 1.0);
}

