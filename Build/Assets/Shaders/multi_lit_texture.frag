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
	float intensity;
	float range;
	float innerAngle;
	float outerAngle;
} lights[3];

vec3 ambientLight = vec3(0.2, 0.2, 0.2);
uniform int numLight = 3;

//vec3 diffuseLight = vec3(1, 1, 1);
//vec3 lightPosition = vec3(0, 8, 0);

void phong(in Light light, in vec3 position, in vec3 normal, out vec3 diffuse, out vec3 specular)
{
	// DIFFUSE
	vec3 lightDir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(light.position - position);

	float spotIntensity = 1;
	if (light.type == SPOT)
	{
		float angle = acos(dot(light.direction, -lightDir));
		//if (angle > light.innerAngle) spotIntensity = 0;
		spotIntensity = smoothstep(light.outerAngle + 0.001, light.innerAngle, angle);
	}

	float intensity = max(dot(lightDir, normal), 0) * spotIntensity;
	diffuse = material.diffuse * (light.color * intensity);

	// SPECULAR
	specular = vec3(0);
	if (intensity > 0) 
	{
		vec3 reflection = reflect(-lightDir, normal);
		vec3 viewDir = normalize(-position);
		intensity = max(dot(reflection, viewDir), 0);
		intensity = pow(intensity, material.shininess);
		specular = material.specular * intensity * spotIntensity;
	}
}
/*
vec3 ads(in vec3 position, in vec3 normal)
{
	// AMBIENT
	vec3 ambient = ambientLight;

	// ATTENUATION
	float attenuation = 1;
	if (light.type != DIRECTIONAL)
	{
		float distanceSqr = dot(light.position - position, position - position);
		float rangeSqr = pow(light.range, 2.0);

		attenuation = max(0, 1 - pow((distanceSqr/rangeSqr), 2.0));
		attenuation = pow(attenuation, 2.0);
	}

	

	return ambient + (diffuse + specular) * light.intensity * attenuation;
}*/


void main()
{
	vec4 texcolor = texture(tex, ftexcoord);
	ocolor = vec4(ambientLight, 1);
	
	for (int i = 0; i < numLight; i++)
	{
		vec3 diffuse;
		vec3 specular;

		phong(lights[i], fposition, fnormal, diffuse, specular);
		ocolor += (vec4(diffuse, 1) * texcolor) + vec4(specular, 1);
	}
}
