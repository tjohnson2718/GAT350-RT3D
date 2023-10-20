#version 430

in layout(location = 0) vec3 fposition;
in layout(location = 1) vec3 fnormal;
in layout(location = 2) vec2 ftexcoord;
in layout(location = 3) vec4 fcolor;

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
	vec3 position;
	vec3 color;
} light;

vec3 ambientLight = vec3(0.2, 0.2, 0.2);
vec3 diffuseLight = vec3(1, 1, 1);
vec3 lightPosition = vec3(0, 8, 0);

vec3 ads(in vec3 position, in vec3 normal)
{
	// AMBIENT
	vec3 ambient = ambientLight;

	// DIFFUSE
	vec3 lightDir = normalize(lightPosition - position);
	float intensity = max(dot(lightDir, normal), 0);
	vec3 diffuse = material.diffuse * (diffuseLight * intensity);

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
	//ocolor = texcolor * fcolor;
	ocolor = vec4(ads(fposition, fnormal), 1);
}
