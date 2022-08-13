#version 120

uniform vec3 lightPos;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float s;

varying vec3 normal; // in camera space
varying vec3 vPos;

void main()
{
	vec3 n = normalize(normal);
	vec3 lightDir = lightPos - vPos;
	float distance = length(lightDir);
	distance = distance * distance;
	vec3 l = normalize(lightDir);
	vec3 cd = kd * max(0, dot(l, n));

	vec3 viewDir = normalize(-vPos);
	vec3 halfDir = normalize(l + viewDir);
	float specAngle = max(dot(halfDir, n), 0.0);

	vec3 cs = ks * pow(specAngle, s);

	vec3 color = ka + cd + cs;
	gl_FragColor = vec4(color.r, color.g, color.b, 1.0);
}
