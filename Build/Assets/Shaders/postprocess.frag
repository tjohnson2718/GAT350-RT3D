#version 430

#define INVERT_MASK		 (1 << 0)
#define GRAYSCALE_MASK	 (1 << 1)
#define COLORTINT_MASK	 (1 << 2)
#define GRAIN_MASK		 (1 << 3)
#define SCANLINE_MASK    (1 << 4)
#define VIGNETTE_MASK    (1 << 5)
#define RADIAL_BLUR_MASK (1 << 6)


in layout(location = 0) vec2 ftexcoord;
out layout(location = 0) vec4 ocolor;

uniform float blend = 0;
uniform uint params = 0;

layout(binding = 0) uniform sampler2D screenTexture;

vec4 invert(in vec4 color)
{
	return vec4(vec3(1) - color.rgb, color.a);
}

vec4 grayscale(in vec4 color)
{
	return vec4(vec3(0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b), color.a);
}

float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec3 applyColorTint(vec3 color, vec3 tint) {
    return color * tint;
}

vec3 applyGrain(vec3 color, vec2 texCoord) {
    float grain = rand(texCoord) * 0.5;
    return color + grain;
}

vec3 applyScanline(vec3 color, vec2 texCoord) {
    float scanlineIntensity = 0.5;
    float scanline = mod(texCoord.y * 500.0, 2.0) < 1.0 ? 1.0 - scanlineIntensity : 1.0;
    return color * scanline;
}

vec3 applyVignette(vec3 color, vec2 texCoord) {
    float vignetteIntensity = 0.4; // Adjust the intensity of the vignette
    float radius = length(texCoord - 0.5);
    return color * smoothstep(1.0, 1.0 - vignetteIntensity, radius);
}

vec3 applyRadialBlur(vec3 color, vec2 texCoord) {
    float blurAmount = 0.02; // Adjust the amount of radial blur
    vec2 center = vec2(0.5, 0.5);
    vec2 offset = texCoord - center;
    float radialBlurFactor = exp(-dot(offset, offset) / blurAmount);
    return mix(color, color * radialBlurFactor, 0.5); // Adjust the mix factor
}

void main()
{
	vec4 basecolor = texture(screenTexture, ftexcoord);
	vec4 postprocess = basecolor;

	if (bool(params & INVERT_MASK)) postprocess = invert(postprocess);
	if (bool(params & GRAYSCALE_MASK)) postprocess = grayscale(postprocess);
	if (bool(params & COLORTINT_MASK)) {
        vec3 tint = vec3(1.0, 0.5, 0.5); 
        postprocess.rgb = applyColorTint(postprocess.rgb, tint);
    }
	if (bool(params & GRAIN_MASK)) postprocess.rgb = applyGrain(postprocess.rgb, ftexcoord);
    if (bool(params & SCANLINE_MASK)) postprocess.rgb = applyScanline(postprocess.rgb, ftexcoord);
    if (bool(params & VIGNETTE_MASK)) postprocess.rgb = applyVignette(postprocess.rgb, ftexcoord);
    if (bool(params & RADIAL_BLUR_MASK)) postprocess.rgb = applyRadialBlur(postprocess.rgb, ftexcoord);

	ocolor = mix(basecolor, postprocess, blend);
}
