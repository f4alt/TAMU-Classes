#version 120

uniform vec3 lightInfo[4];

varying vec3 normal; // in camera space
varying vec3 vPos;

void main()
{
	vec3 n = normalize(normal);
	vec3 lt_dir1 = normalize(lightInfo[0] - vPos);
	vec3 lt_dir2 = normalize(lightInfo[2] - vPos);
	float calc1 = dot(normal, lt_dir1);
	float calc2 = dot(normal, lt_dir2);
	float li = calc1;
	vec3 res;

	if (li <= 0.5) {
		res = vec3(0.0f);
	} else {
		res = vec3(1.0f);
	}

	gl_FragColor = vec4(res, 1.0);
}
