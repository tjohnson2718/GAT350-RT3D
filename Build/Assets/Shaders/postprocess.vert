#version 430

in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;

out layout(location = 0) vec2 otexcoord;

void main()
{
	otexcoord = vtexcoord;
	gl_Position = vec4(vposition, 1.0);
}

