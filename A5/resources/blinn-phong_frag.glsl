#version 120

uniform vec3 lightInfo[40];
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float s;
uniform sampler2D texture0;

varying vec3 normal; // in camera space
varying vec3 vPos;
varying vec2 vTex;

vec3 calcDirLight(vec3 lightPos, vec3 n, vec3 lightColor) {
	float lightPower = 1.0;
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

	vec3 color = kd * lambertian * lightColor * lightPower / distance + ks * specular * lightColor * lightPower / distance;

	//vec3 color = kd * lambertian * lightColor + ks * specular * lightColor;

	return color;
}

vec3 attenuationLight(vec3 lightPos, vec3 n, vec3 lightColor) {
	vec3 lightDir = lightPos - vPos;
	float distance = length(lightDir);
	float distance2 = distance * distance;
	lightDir = normalize(lightDir);

	float lambertian = max(dot(lightDir, n), 0.0);
	float specular = 0.0;

	if (lambertian > 0.0){
		vec3 viewDir = normalize(-vPos);

		vec3 halfDir = normalize(lightDir + viewDir);
		float specAngle = max(dot(halfDir, n), 0.0);
		specular = pow(specAngle, s);
	}

	vec3 color = lightColor * (kd * lambertian + ks * specular);
	float attenuation = 1.0 / (1.0 + .0429 * distance + .9857 * distance2);

	return color * attenuation;
}

void main()
{
	vec3 n = normalize(normal);

	vec3 res = ka;

	for (int i=0; i < 20; i++) {
		res += attenuationLight(lightInfo[2*i], n, lightInfo[2*i+1]);
	}

	gl_FragColor = vec4(res, 1.0);

	//gl_FragColor = texture2D(texture0, vTex0);
}
