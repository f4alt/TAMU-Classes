#version 120

varying vec3 normal; // in camera space

void main()
{
	vec3 n = normalize(normal);
	vec3 color = 0.5 * (n + 1.0);
	gl_FragData[0] = vec4(color.r, color.g, color.b, 1.0);
	gl_FragData[1] = vec4(0.0, 0.0, 1.0, 1.0);
}
