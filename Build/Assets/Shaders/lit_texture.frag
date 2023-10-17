#version 430

in layout(location = 0) vec2 texcoord;
in layout(location = 1) vec3 normal;

out layout(location = 0) vec4 ocolor;

uniform vec4 color;
uniform vec2 offset;
uniform vec2 tiling;

layout(binding = 0) uniform sampler2D tex;

void main()
{
	vec4 texcolor = texture(tex, (texcoord * tiling) + offset);
	ocolor = texcolor * color;
}
