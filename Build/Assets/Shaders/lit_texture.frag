#version 430

#define POINT		0
#define DIRECTIONAL 1
#define SPOT		2

in layout(location = 0) vec3 fposition;
in layout(location = 1) vec3 fnormal;
in layout(location = 2) vec2 ftexcoord;
//in layout(location = 3) vec4 fcolor;

out layout(location = 0) vec4 ocolor;

layout(binding = 0) uniform sampler2D tex;

uniform struct Material
{
	vec3 diffuse;
	vec3 specular;
	float shininess;

	vec2 offset;
	vec2 tiling;
} material;


uniform struct Light
{
	int type;
	vec3 position;
	vec3 direction;
	vec3 color;
	float cutoff;
} light;

vec3 ambientLight = vec3(0.2, 0.2, 0.2);
vec3 diffuseLight = vec3(1, 1, 1);
vec3 lightPosition = vec3(0, 8, 0);

vec3 ads(in vec3 position, in vec3 normal)
{
	// AMBIENT
	vec3 ambient = ambientLight;

	// DIFFUSE
	vec3 lightDir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(light.position - position);

	float spotIntensity = 1;
	if (light.type == SPOT)
	{
		float angle = acos(dot(light.direction, -lightDir));
		if (angle > light.cutoff) spotIntensity = 0;
	}

	float intensity = max(dot(lightDir, normal), 0);
	vec3 diffuse = material.diffuse * (light.color * intensity * spotIntensity);

	// SPECULAR
	vec3 specular = vec3(0);
	if (intensity > 0) 
	{
		vec3 reflection = reflect(-lightDir, normal);
		vec3 viewDir = normalize(-position);
		intensity = max(dot(reflection, viewDir), 0);
		intensity = pow(intensity, material.shininess);
		specular = material.specular * intensity;
	}

	return ambient + diffuse + specular;
}


void main()
{
	vec4 texcolor = texture(tex, ftexcoord);
	ocolor = texcolor * vec4(ads(fposition, fnormal), 1);
}
