#version 120

uniform sampler2D posTexture;
uniform sampler2D norTexture;
uniform sampler2D keTexture;
uniform sampler2D kdTexture;
uniform vec2 windowSize;

uniform vec3 lightInfo[100];

// global variables
vec3 n;
vec3 vPos;
vec3 kd;
vec3 ks = vec3(0.0f);
float s = 0.0;

vec3 attenuationLight(vec3 lightPos, vec3 lightColor) {
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
    vec2 tex;
    tex.x = gl_FragCoord.x/windowSize.x;
    tex.y = gl_FragCoord.y/windowSize.y;

    // Fetch shading data
    vPos = texture2D(posTexture, tex).rgb;
    vec3 nor = texture2D(norTexture, tex).rgb;
    vec3 ke = texture2D(keTexture, tex).rgb;
    kd = texture2D(kdTexture, tex).rgb;

		n = normalize(nor);
		vec3 res = ke;

		// we know non lights have ke = 0, and we are setting all ks to be uniform
		if (ke.r == 0 && ke.g == 0 && ke.b == 0) {
			ks = vec3(1.0f);
			s = 10.0;
		}

		for (int i=0; i < 50; i++) {
			res += attenuationLight(lightInfo[2*i], lightInfo[2*i+1]);
		}

		// *****************************************************************
		// ***** UNCOMMENT VARIOUS OPTIONS TO CHECK THE 4 COMBINATIONS *****
		// *****************************************************************
    gl_FragColor.rgb = vec3(res);
		//gl_FragColor.rgb = pos;
		//gl_FragColor.rgb = n;
		//gl_FragColor.rgb = ke;
		//gl_FragColor.rgb = kd;
}
