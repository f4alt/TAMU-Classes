#version 120

uniform vec3 lightInfo[4];
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float s;

varying vec3 normal; // in camera space
varying vec3 vPos;

vec3 calcDirLight(vec3 lightPos, vec3 n, vec3 lightColor) {
	//float lightPower = 5.0;
	vec3 lightDir = lightPos - vPos;
	float distance = length(lightDir);
	distance = distance * distance;
	lightDir = normalize(lightDir);

	float lambertian = max(dot(lightDir, n), 0.0);
	float specular = 0.0;

	if (lambertian > 0.0){
		vec3 viewDir = normalize(-vPos);

		vec3 halfDir = normalize(lightDir + viewDir);
		float specAngle = max(dot(halfDir, n), 0.0);
		specular = pow(specAngle, s);
	}

	//vec3 color = ka + kd * lambertian * lightColor * lightPower / distance + ks * specular * lightColor * lightPower / distance;

	vec3 color = kd * lambertian * lightColor + ks * specular * lightColor;

	return color;
}

void main()
{
	vec3 n = normalize(normal);

	vec3 res = ka;

	res += calcDirLight(lightInfo[0], n, lightInfo[1]);
	res += calcDirLight(lightInfo[2], n, lightInfo[3]);

	gl_FragColor = vec4(res, 1.0);
}
