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
	vec3 lt_dir1 = normalize(lightInfo[0] - vPos);
	vec3 lt_dir2 = normalize(lightInfo[2] - vPos);
	float calc1 = dot(normal, lt_dir1);
	float calc2 = dot(normal, lt_dir2);
	float li = calc1;
	vec3 res;

	// blinn phong calc
	res = ka;
	res += calcDirLight(lightInfo[0], n, lightInfo[1]);
	res += calcDirLight(lightInfo[2], n, lightInfo[3]);

	// quantize colors
	if (res.r < 0.25) {
		res.r = 0.0;
	} else if (res.r < 0.5) {
		res.r = 0.25;
	} else if (res.r < 0.75) {
		res.r = 0.5;
	} else if (res.r < 1.0) {
		res.r = 0.75;
	} else {
		res.r = 1.0;
	}

	if (res.g < 0.25) {
		res.g = 0.0;
	} else if (res.g < 0.5) {
		res.g = 0.25;
	} else if (res.g < 0.75) {
		res.g = 0.5;
	} else if (res.g < 1.0) {
		res.g = 0.75;
	} else {
		res.g = 1.0;
	}

	if (res.b < 0.25) {
		res.b = 0.0;
	} else if (res.b < 0.5) {
		res.b = 0.25;
	} else if (res.b < 0.75) {
		res.b = 0.5;
	} else if (res.b < 1.0) {
		res.b = 0.75;
	} else {
		res.b = 1.0;
	}

	// apply silhouette
	if (li < 0.3) {
		res = vec3(0.0f);
	}

	gl_FragColor = vec4(res, 1.0);
}
